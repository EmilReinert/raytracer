// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
	, scene_(scene)
{}


void Renderer::render()
{
  const std::size_t checkersize = 20;
	Camera cam{"camera1",20};
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
	
      /*
	/// gitter muster
	
	if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

	
*/

	Ray casted=cam.castRay(x,y,width_,height_);
	float distance = 100000000;
	
	Intersection i = findIntersection(casted, distance);
	p.color = compute_color(casted,i,3);
	write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}


Color const Renderer::compute_color(Ray const& ray, Intersection const & inter, int depth){
	if(inter.getShape()){
		Color clr =  getAmbient(inter.getShape()->get_material().m_ka,inter);//ambient
		auto light_map = whatLight(inter);
		if(isLight(inter)){
			//actual in light
			float intensity_normal = normal_intensity(light_map,inter);
			//clr = clr+(intensity_normal*0.5);
			//std::cout<<"-"<<intensity_normal;
		}
		//reflection
		if (depth>0){
			Color reflection_clr=reflection(ray,inter,depth);
			clr = clr+(reflection_clr*0.5);
		}
		//refraction
		if (inter.getShape()->get_material().m_opacity>0.0f){
			Color refraction_clr= refraction(ray,inter,depth);//std::cout<<refraction_clr;
			clr =clr*(1-inter.getShape()->get_material().m_opacity*0.01)- refraction_clr*inter.getShape()->get_material().m_opacity*0.01;
		}
		//std::cout<<clr;
		return clr;//.final_color();
	}
	
	return Color(0.5,0.5,0.5);//backgroundcolor;
}

float const Renderer::normal_intensity(std::map<std::shared_ptr<Light>,float > & lightMap,  Intersection const & inter){
	float intensity;
	for (std::map<std::shared_ptr<Light>,float >::iterator it = lightMap.begin();it!=lightMap.end();it++){
		auto point = inter.getPosition();
		Ray light_ray{point,it->first->getSource()-point};
		auto a = glm::normalize(light_ray.m_direction);
		auto b = glm::normalize(inter.getNormal());
		//std::cout<<Ray{glm::vec3{0.0},inter.getNormal()};
		float holder = (a.x*b.x+a.y*b.y+a.z*b.z)*(it->second);
		if(holder>0&&isLight(inter)){intensity+= holder; }else {intensity=0;}
		
	}
	return intensity;

}

Intersection const Renderer::findIntersection(Ray const&ray, float distance){
	float distance_to_object= 100000000000000000;
	std::shared_ptr<Shape> shape_ptr;
	Intersection i;
	for(std::shared_ptr<Shape> shp: scene_.m_shapes){ 
		Intersection inter = shp->realintersect(ray,distance);
		if(inter.isHit()&&inter.getDistance()< distance_to_object){//&&inter.getShape()!=shp){
			shape_ptr = inter.getShape();
			distance_to_object = inter.getDistance();
			i = inter;
			
		}
	}
	return i;
}


std::map<std::shared_ptr<Light>,float > const Renderer::whatLight(Intersection const&inter){
	std::map<std::shared_ptr<Light>,float> lightMap;
	for(std::shared_ptr<Light> lght: scene_.m_lights){
		bool hit=false;
		auto point = inter.getPosition();
		Ray light_ray{point,lght->getSource()-point};
		float distance =10000000.0f;
		for(std::shared_ptr<Shape> shp: scene_.m_shapes){ 
			Intersection holderintersection = shp->realintersect(light_ray,distance);
			if(holderintersection.isHit()){
				if(holderintersection.getShape()->get_material().m_opacity>0){
				lightMap[lght]=holderintersection.getShape()->get_material().m_opacity*0.01;}
				else{lightMap[lght]=0.0f;}
			}
			
		}
		lightMap[lght]=lght->getIntensity();
	}
 	return lightMap;
}


Color const Renderer::getAmbient(Color const& clr, Intersection const&inter)const{
	/*auto point = inter.getPosition();
	Ray ambient_ray{point,scene_.m_ambient_light.getSource()-point};
	float distance =100000000.0f;
	if(!inter.getShape()->intersect(ambient_ray,distance)){*/
	auto col =clr;
	return col*0.1;
	}


Color const Renderer::reflection(Ray const & ray,Intersection const & inter, int depth){
	Ray normalRay{inter.getPosition(),inter.getNormal()};
	Ray toBeMirrored{inter.getPosition(),ray.m_direction};
	Ray  mirrorRay= toBeMirrored.reflectionRay(normalRay);
	float distance = 100000000;
	//light reflection
	Color lightInter = findLightIntersection(mirrorRay,distance);
	if(lightInter!=Color()){
		return lightInter;}
	Intersection i = findIntersection(mirrorRay, distance);
	Color clr =compute_color(mirrorRay,i,depth-1);
	if(i.getShape()){return clr;}
	return Color(0.5,0.5,0.5);
	

}
Color const Renderer::findLightIntersection(Ray const&ray, float distance)const{
	for(std::shared_ptr<Light> lght: scene_.m_lights){ 
		bool hit = lght->intersect(ray,distance);
		if(hit){std::cout<<hit;
			return lght->getColor();}
	}
	return Color();
}

Color const Renderer::refraction(Ray const & ray,Intersection const & inter, int depth){
	Ray normalRay{inter.getPosition(),inter.getNormal()};
	Ray toBeMirrored{inter.getPosition(),-ray.m_direction};
	Ray  refractRay= toBeMirrored.refractionRay(normalRay);
	Ray refractionRay{(inter.m_position + (0.00001f * refractRay.m_direction)), refractRay.m_direction};
	float distance = 100000000;
	//std::cout<<refractionRay;
	Intersection i = findIntersection(refractionRay, distance);
	Color clr =compute_color(refractionRay,i,depth);
	if(i.getShape()&&i.getShape()!=inter.getShape()){
		//std::cout<<clr<<i;
		return clr;}
	return Color(0.5,0.5,0.5);//background
}
bool const Renderer::isLight(Intersection const&inter)const{
	for(std::shared_ptr<Light> lght: scene_.m_lights){
		auto point = inter.getPosition();
		Ray light_ray{point,lght->getSource()-inter.getPosition()};
		float distance =100000.0f;
		if(!inter.getShape()->intersect(light_ray,distance)){return true;}
	return false;}
 	return false;
}




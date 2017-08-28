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


Intersection const Renderer::findIntersection(Ray const&ray, float distance){
	float distance_to_object= 100000000000000000;
	Shape* shape_ptr;
	Intersection i;
	for(std::shared_ptr<Shape> shp: scene_.m_shapes){ 
		Intersection inter = shp->realintersect(ray,distance);
		if(inter.isHit()&&inter.getDistance()< distance_to_object){
			shape_ptr = inter.getShape();
			distance_to_object = inter.getDistance();
			i = inter;
			
		}
	}
	return i;
}

std::vector<std::shared_ptr<Light>> const Renderer::isLight(Intersection const&inter)const{
	std::vector<std::shared_ptr<Light>> lightVec;
	for(std::shared_ptr<Light> lght: scene_.m_lights){
		bool hit=false;
		auto point = inter.getPosition();
		Ray light_ray{point,lght->getSource()-point};
		float distance =10000000.0f;
		for(std::shared_ptr<Shape> shp: scene_.m_shapes){ 
			if(shp->intersect(light_ray,distance)){
				return std::vector<std::shared_ptr<Light>>();
			}
		}
		lightVec.push_back(lght);
	}
 	return lightVec;
}

Color const Renderer::compute_color(Ray const& ray, Intersection const & inter, int depth){
	if(inter.getShape()){
		Color clr =  getAmbient(inter.getShape()->get_material().m_ka,inter);//ambient
		auto light_vec = isLight(inter);
		if(!light_vec.empty()){
			//actual in light
			float intensity_normal = normal_intensity(light_vec,inter);
			clr = clr+intensity_normal;
		}
		//reflection
		if (depth>0){
			Color reflection_clr=reflection(ray,inter,depth);
			clr = clr+reflection_clr;}
		
		return clr;
	}
	
	return Color{0.5,0.5,0.5};//backgroundcolor;
	


}

Color const Renderer::getAmbient(Color const& clr, Intersection const&inter)const{
	/*auto point = inter.getPosition();
	Ray ambient_ray{point,scene_.m_ambient_light.getSource()-point};
	float distance =100000000.0f;
	if(!inter.getShape()->intersect(ambient_ray,distance)){*/
	auto col =clr;
	return col-0.7;
	}

float const Renderer::normal_intensity(std::vector<std::shared_ptr<Light>> const & lightVec,  Intersection const & inter){
	
	for (std::shared_ptr<Light> lght: lightVec){
		auto point = inter.getPosition();
		Ray light_ray{point,lght->getSource()-point};
		auto a = glm::normalize(light_ray.m_direction);
		auto b = glm::normalize(inter.getNormal());
		return a.x*b.x+a.y*b.y+a.z*b.z; 
		
	}
	return 0;

}
Color const Renderer::reflection(Ray const & ray,Intersection const & inter, int depth){
	Ray normalRay{inter.getPosition(),inter.getNormal()};
	Ray toBeMirrored{inter.getPosition(),-ray.m_direction};
	Ray mirrorRay= toBeMirrored.mirror(normalRay).newLength(1);
	float distance = 100000000;
	Intersection i = findIntersection(mirrorRay, distance);
	//if(i.getShape()){std::cout<<i<<"\n";}
	Color clr =compute_color(mirrorRay,i,depth-1);
	Color untergrenze = Color{0.01,0.01,0.01};
	return clr*0.5;

}



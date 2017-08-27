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
	auto shape_ptr = i.getShape();
	p.color = compute_color(shape_ptr,i);
	shape_ptr = 0;//IMPORTANT
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

std::shared_ptr<Light> const Renderer::isLight(Intersection const&inter)const{
	for(std::shared_ptr<Light> lght: scene_.m_lights){
		auto point = inter.getPosition();
		Ray light_ray{point,lght->getSource()-point};
		float distance =100000.0f;
		for(std::shared_ptr<Shape> shp: scene_.m_shapes){ 
			if(shp->intersect(light_ray,distance)){
				return lght;
			}
		}
	return 0;}
 	return 0;
}

Color const Renderer::compute_color(Shape* const& shp, Intersection const & inter){
	Color clr =  Color{0.5,0.5,0.5};//backgroundcolor
	if(shp){
		Light light_ptr = isLight(inter);
		if(!light_ptr){
			shp->get_material().m_ka;}
		else{
			//AMBIENT
			Color clr = getAmbient(shp->get_material().m_ka,inter);
			return clr;
		}
	}
	return clr;
	


}

Color const Renderer::getAmbient(Color const& clr, Intersection const&inter)const{
	auto point = inter.getPosition();
	Ray ambient_ray{point,scene_.m_ambient_light.getSource()-point};
	float distance =100000000.0f;
	if(!inter.getShape()->intersect(ambient_ray,distance)){
		auto col =clr;
		return col-Color{0.5,0.5,0.5};}
	return Color{0.0,0.0,0.0};
}
//Color const Renderer::final_color(Light const& light



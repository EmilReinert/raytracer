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
	Camera cam{"camera1",90};
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      /*
	/// gitter muster
	
	if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }*/

	Ray casted=cam.castRay(p,width_,height_);
	float distance = 100;
	auto shape_ptr = findShape(casted,distance);
	std::cout<<(bool)shape_ptr;
	if(shape_ptr){p.color = shape_ptr->get_material().m_ka; }
	else{p.color = Color{0.1,0.1,0.1};}
		
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


std::shared_ptr<Shape> const Renderer::findShape(Ray const&ray, float distance){
	for(std::shared_ptr<Shape> shp: scene_.m_shapes){ 
		if(!shp->realintersect(ray,distance).isHit()){
			distance = shp->realintersect(ray,distance).getDistance(); 
			return shp;}}
	return 0;
}







// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include <iostream>
#include "color.hpp"
#include <vector>
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "shape.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "light.hpp"

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
	Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render();
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }
  
  Intersection const findIntersection(Ray const&ray,float distances);
  std::vector<std::shared_ptr<Light>> const isLight( Intersection const& inter)const;
  Color const compute_color(Ray const&ray, Intersection const & inter, int depth);
  Color const getAmbient(Color const& clr, Intersection const & inter)const;
  float const normal_intensity(std::vector<std::shared_ptr<Light>> const & lightVec,Intersection const & inter);
  Color const reflection(Ray const&ray,Intersection const & inter, int depth);



private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
	Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP

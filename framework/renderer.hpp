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
#include <map>
class Renderer
{
public:
  Renderer();
  Renderer(unsigned w, unsigned h, std::string const& file);
	Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render();
  void write(Pixel const& p);
  void setFilename(std::string name);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }
  bool const isLight(Intersection const&inter)const;
  Intersection const findIntersection(Ray const&ray,float distances);
  std::map<std::shared_ptr<Light>,float > const whatLight( Intersection const& inter);
  Color const compute_color(Ray const&ray, Intersection const & inter, int depth);
  Color const getAmbient(Color const& clr, Intersection const & inter)const;
  float const normal_intensity(std::map<std::shared_ptr<Light>,float > & lightVec,Intersection const & inter);
  Color const reflection(Ray const&ray,Intersection const & inter, int depth);
  Color const findLightIntersection(Ray const&ray, float distance)const;
  Color const refraction(Ray const&ray,Intersection const & inter, int depth);

  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
	Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP

#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "sdfloader.hpp"
#include "light.hpp"
#include <memory>
#include "renderer.hpp"
#include "sphere.hpp"
#include "box.hpp"


int main(int argc, char* argv[])
{
//////// Beispielscene 
	SDFloader loader{};
	Scene scene {};
	std::string bla = "/home/emil/Documents/RAYTRACER/final_program/raytracer/source/material_input.txt";
	scene = loader.load(bla);
	//light
	Light light1{"light1",glm::vec3{10.0f,10.0f, 0.0f},Color{1.0f,1.0f,1.0f}};
	scene.m_lights.push_back(std::make_shared<Light>(light1));
	//shape
	Sphere sphere1{"sphere1", Material{"weiß",Color{1.0f,1.0f,1.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{0.0f,0.0f,-10.0f},3.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere1));
	std::cout<<scene;
////////

	
  unsigned const width = 800;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer app{width, height, filename, scene};

  std::thread thr([&app]() { app.render(); });

  Window win{glm::ivec2{width,height}};

  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
    win.show(app.colorbuffer());
  }

  thr.join();

  return 0;
}

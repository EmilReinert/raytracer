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
	Light light1{"light1",glm::vec3{1000.0f,-1000.0f, -300.0f},1.0f,Color{1.0f,1.0f,1.0f}};
	scene.m_lights.push_back(std::make_shared<Light>(light1));
	//ambient
	Light ambient{"ambientlight",glm::vec3{0.0,0.0,0.0},1.0f,Color{1.0f,1.0f,1.0f}};
	scene.m_ambient_light=ambient;
	//shapes
	Sphere sphere1{"sphere1", Material{"rot",Color{1.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{600.0f,0.0f,-900.0f},300.0f};
	//scene.m_shapes.push_back(std::make_shared<Sphere>(sphere1));

	Sphere sphere2{"sphere2", Material{"blau",Color{0.0f,0.0f,1.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{-600.0f,0.0f,-900.0f},300.0f};
	//scene.m_shapes.push_back(std::make_shared<Sphere>(sphere2));
	
	Sphere sphere3{"sphere3", Material{"grün",Color{0.0f,1.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{0.0f,0.0f,-2000.0f},1000.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere3));



	
	
	Box box {"test_box",
		Material{"",Color{1.0f,0.0f,0.0f},
		Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f},1.0f},
		glm::vec3{600.0f,-200.0f,-1000.0f},	//min
		glm::vec3{1000.0f,-1000.0f,-1500.0f}	//max
	};
	scene.m_shapes.push_back(std::make_shared<Box>(box));
	
	std::cout<<scene;
////////

	
  unsigned const width = 800;
  unsigned const height = 800;
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

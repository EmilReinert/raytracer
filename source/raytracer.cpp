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
	Light light1{"light1",glm::vec3{0.0,100.0,0.0},10.0f,Color{1.0f,1.0f,1.0f}};
	scene.m_lights.push_back(std::make_shared<Light>(light1));
	Light light2{"light2",glm::vec3{1000.0,1000.0,0.0},1.0f,Color{1.0f,1.0f,1.0f}};
	//scene.m_lights.push_back(std::make_shared<Light>(light2));
	//ambient
	Light ambient{"ambientlight",glm::vec3{0.0,0.0,0.0},1.0f,Color{1.0f,1.0f,1.0f}};
	scene.m_ambient_light=ambient;
	//shapes
	
	
	Sphere sphere1{"sphere1", Material{"rott",Color{1.0f,0.0f,0.00f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{400.0f,0.0f,-700.0f},400.0f};
	//scene.m_shapes.push_back(std::make_shared<Sphere>(sphere1));

	Sphere sphere2{"sphere2", Material{"blau",Color{1.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{-200.0f,0.0f,-700.0f},300.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere2));
	
	Sphere sphere3{"sphere3", Material{"rot",Color{1.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f},glm::vec3{0.0f,400.0f,-1000.0f},400.0f};
	//scene.m_shapes.push_back(std::make_shared<Sphere>(sphere3));
	
	Sphere sphere4{"sphere4", Material{"blau",Color{0.5,0.5,0.5},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f,100.0f,12312313.0f},glm::vec3{-50.0f,0.0f,-200.0f},50.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere4));
	


	
	
	Box box {"test_box",
		Material{"",Color{0.0f,0.0f,1.0f},
		Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f},1.0f},
		//min
		glm::vec3{1000.0f,-3000.0f,-1500.0f},
glm::vec3{100.0f,3000.0f,-500.0f}	//max
	};
	scene.m_shapes.push_back(std::make_shared<Box>(box));
	
	std::cout<<scene;
////////

	
  unsigned const width = 1000;
  unsigned const height =1000;
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

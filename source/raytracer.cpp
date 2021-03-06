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
	std::string bla = "/home/emil/Documents/RAYTRACER/program/raytracer/source/material_input.txt";
	scene = loader.load(bla);
	//light
	Light light1{"light1",glm::vec3{0.0,100.0,0.0},10.0f,Color{1.0f,1.0f,1.0f},0.7f};
	scene.m_lights.push_back(std::make_shared<Light>(light1));
	Light light2{"light2",glm::vec3{-80.0,100.0,0.0},50.0f,Color{1.0f,1.0f,1.0f},0.3f};
	scene.m_lights.push_back(std::make_shared<Light>(light2));
	//ambient
	Color ambient{1.0f,1.0f,1.0f};
	scene.m_ambient_light=ambient;
	//shapes
	
	
	Sphere sphere1{"sphere1", Material{"rott",Color{1.0f,0.0f,0.00f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},0.0f},glm::vec3{400.0f,0.0f,-700.0f},400.0f};
	//scene.m_shapes.push_back(std::make_shared<Sphere>(sphere1));

	Sphere sphere2{"sphere2", Material{"blau",Color{1.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},0.3f},glm::vec3{-200.0f,0.0f,-700.0f},300.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere2));
	
	Sphere sphere3{"glasssphere3", Material{"",Color{0.0f,0.0f,0.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},1.0f,100.0f,12312313.0f},glm::vec3{0.0f,30.0f,-200.0f},50.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere3));
	
	Sphere sphere4{"sphere4", Material{"blau",Color{0.0,0.0,1.0},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},0.3f},glm::vec3{20.0f,200.0f,-400.0f},50.0f};
	scene.m_shapes.push_back(std::make_shared<Sphere>(sphere4));
	
	
	Box box1 {"box1",
		Material{"",Color{0.0f,1.0f,1.0f},Color{1.0f,1.0f,1.0f},
		Color{1.0f,1.0f,1.0f},0.0f},
		//min
		glm::vec3{-5000.0f,-3000.0f,-150.0f},
glm::vec3{100.0f,-200.0f,-25000.0f}	//max
	};
	//scene.m_shapes.push_back(std::make_shared<Box>(box1));
	
	
	
	Box box2 {"mirrorwall",
		Material{"",Color{0.0f,0.0f,0.0f},
		Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f},0.7f},
		//min
		glm::vec3{1000.0f,-3000.0f,-1500.0f},
glm::vec3{100.0f,3000.0f,0.0f}	//max
	};
	//scene.m_shapes.push_back(std::make_shared<Box>(box2));
	
	//composites
	Composite comp{"boxes"};
	comp.add_shape(std::make_shared<Box>(box1));
	comp.add_shape(std::make_shared<Box>(box2));
	scene.m_composites.push_back(std::make_shared<Composite>(comp));
	
	Camera cam("cam",20);
	scene.m_camera = cam;
	
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

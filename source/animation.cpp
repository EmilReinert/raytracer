#include <catch.hpp>

#include <renderer.hpp>
#include <iostream>
#include <fstream>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
//include classes for testing
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "color.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "camera.hpp"
#include <string> 
#include <cmath>

int main(){

	SDFloader loader{};
	Scene scene = loader.load("/home/emil/Documents/RAYTRACER/program/raytracer/source/animation.txt");
	std::cout<<scene;
	
	
	unsigned const width = 200;
	unsigned const height =200;
	std::string  filename = "1";
	
	
	Renderer app{width, height, filename, scene};


	for(int i; i<=100;i++){
		filename = std::to_string(i);
		app.filename_=filename;

		std::shared_ptr<Shape> it = *scene.m_shapes.begin();
		float z_dir = 2*12.73*i;
		float y_dir = ((20*sin(0.2*i))*(20*sin(0.2*i)));
		if(i<=63){y_dir=y_dir-(6.36619*i);}
		std::cout<<y_dir<<"\n";
		std::cout<<z_dir<<"\n";
		
		glm::vec3 direction (0.0f,y_dir,z_dir);
		it->translate(direction);	


		std::thread thr([&app]() { app.render(); });	 
		thr.join();
		std::cout<<"||frame "<<i+1<<" rendered||\n";
	}


	return 0;


};

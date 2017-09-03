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

int main(){

	SDFloader loader{};
	Scene scene = loader.load("/home/emil/Documents/RAYTRACER/program/raytracer/source/animation.txt");
	std::cout<<scene;
	
	
	unsigned const width = 100;
	unsigned const height =100;
	std::string  filename = "1";
	
	
	Renderer app{width, height, filename, scene};


	for(int i; i<=10;i++){
		filename = std::to_string(i);
		app.filename_=filename;

		std::shared_ptr<Shape> it = *scene.m_shapes.begin();
		float z_dir = i*100;
		float y_dir = 0.0f;
		
		
		glm::vec3 direction (0.0f,y_dir,z_dir);
		it->translate(direction);	


		std::thread thr([&app]() { app.render(); });	 
		thr.join();
		std::cout<<"||frame "<<i+1<<" rendered||\n";
	}


	return 0;


};

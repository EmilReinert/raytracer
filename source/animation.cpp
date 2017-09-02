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
	Scene scene = loader.load("/home/emil/Documents/RAYTRACER/final_program/raytracer/source/animation.txt");
	std::cout<<scene;
	
	
	unsigned const width = 300;
	unsigned const height =300;
	std::string  filename = "1";
	
	
	Renderer app{width, height, filename, scene};


	for(int i; i<2;i++){
	filename = std::to_string(i);
	app.filename_=filename;

	auto it = scene.m_shapes.begin();










		std::thread thr([&app]() { app.render(); });	 
	thr.join();
	}


	return 0;


};

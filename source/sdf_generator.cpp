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

int main(){

	SDFloader loader{};
	Scene s1 = loader.load("/home/emil/Documents/RAYTRACER/final_program/raytracer/source/sdf_scene.txt");
	std::cout<<s1;
	return 0;
};



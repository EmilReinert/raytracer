
//scene struct

#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <glm/vec3.hpp>
#include <memory>
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include <map>
#include "camera.hpp"
#include "composite.hpp"
struct Scene
{

    //Camera
    Camera m_camera;

    //Ambient Light
    Color m_ambient_light= Color(0.0f,0.0f,0.0f);

    //Lights
    std::vector<std::shared_ptr<Light>> m_lights;

    //Materials
    std::map<std::string,Material> m_materials;

    //Shapes
    std::vector<std::shared_ptr<Shape>> m_shapes;

    //Composites
    std::vector<Composite> m_composites; 

	std::ostream& print(std::ostream & os){
		std::cout<<"\nScene: \n";

		if (m_ambient_light == Color(0.0f,0.0f,0.0f)){
			os<<"\n----no ambient added yet----\n";} 
		else{
			os<<"\nAmbient Light: "<<m_ambient_light;}
		if(m_materials.empty()){
			os<<"\n----no materials added yet----\n";}
		else{
			int i=1;
			for(auto it = m_materials.cbegin(); it!=m_materials.cend();it++){
				os<<"\nMaterial "<<i<<": "<< it->first;i++;}}
		if(m_lights.empty()){
			os<<"\n----no lights added yet----\n";}
		else{
			int i = 1;
			for(std::shared_ptr<Light> lght: m_lights){
				os<<"\nLight "<<i<<": "<< lght->getName();
				i++;}}
		if(m_shapes.empty()){os<<"\n----no shapes added yet----\n";}
		else{
			int i = 1;
			for(std::shared_ptr<Shape> shp: m_shapes){
				os<<"\nShape "<<i<<": "<< shp->get_name();
				i++;}}
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, Scene & sc)
		{return sc.print(os);}
};

#endif //BUW_SCENE_HPP

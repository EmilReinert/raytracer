
//scene struct

#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <glm/vec3.hpp>
#include <memory>
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"

struct Scene
{
    //Camera
    //Camera m_camera;

    //Ambient Light
    Light m_ambient_light;

    //Lights
    std::vector<std::shared_ptr<Light>> m_lights;

    //Materials
    std::vector<Material> m_materials;

    //Shapes
    std::vector<std::shared_ptr<Shape>> m_shapes;

    //Composites
    //std::vector<Composite> m_composites; 

	std::ostream& print(std::ostream & os)const{
		//if (m_ambient_light == nullptr){os<<"\n----no shapes added yet----\n";} else{os<<"\nAmbient Light: "<<m_ambient-light;}
		if(m_lights.empty()){os<<"\n----no lights added yet----\n";}
		else{int i = 1;
		for(std::shared_ptr<Light> lght: m_lights)
			{os<<"\nLight "<<i<<": "<< lght->getName();i++;}}
		if(m_shapes.empty()){os<<"\n----no shapes added yet----\n";}
		else{int i = 1;
		for(std::shared_ptr<Shape> shp: m_shapes){os<<"\nShape "<<i<<": "<< shp->get_name();i++;}}
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, Scene const& sc)
		{return sc.print(os);}
};

#endif //BUW_SCENE_HPP

#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"
#include <string>
#include "ray.hpp"
#include <cmath>
#include "math.h"
#include "pixel.hpp"

class Camera{

std::string m_name;
unsigned m_fov;
glm::vec3 m_position;
glm::vec3 m_direction;
glm::vec3 m_up;

public:
	
	Camera();
	Camera(std::string const& name, unsigned const&fov);
	Camera(std::string const& name, unsigned const&fov,glm::vec3 const&position,glm::vec3 const&direction,glm::vec3 up);
	std::string getName() const;
	unsigned getFov() const;
	glm::vec3 getPosition() const;
	glm::vec3 getDirection() const;
	glm::vec3 getUp() const;
	
	friend std::ostream& operator<<(std::ostream& os, Camera const& cam)
   	 {
    	    os <<"\nCamera: "<<cam.m_name;
		os<<"\nFov: "<<cam.m_fov;
		os<<"\nPostion: ("<<cam.m_position.x << ", "<< cam.m_position.y  <<", "<< cam.m_position.z <<")";
		os<<"\nDirection: ("<<cam.m_direction.x << ", "<< cam.m_direction.y <<", "<< cam.m_direction.z<<")";
		os<<"\nUp-Vector: ("<<cam.m_up.x << ", "<< cam.m_up.y <<", "<< cam.m_up.z<<")";
        return os;
    }

	Ray castRay(Pixel const& pix, int resolution_x, int resolution_y )const;





};



#endif

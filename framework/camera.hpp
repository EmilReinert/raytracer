#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"
#include <string>



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
	





};



#endif

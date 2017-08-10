#ifndef BUW_INTERSECTION_HPP
#define BUW_INTERSECTION_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <string>
#include <cmath>



class Intersection{
	glm::vec3 m_position;
	glm::vec3 m_direction;
	float distance;


public:
	Intersection();
	Intersection(glm::vec3 const&position, glm::vec3 const& direction, float const& distance);


};




#endif

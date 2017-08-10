#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <string>




class Intersection{
	glm::vec3 m_position;
	glm::vec3 m_direction;
	double m_distance;


public:
	Intersection():
		m_position{glm::vec3{0.0f,0.0f,0.0f}},
		m_direction{glm::vec3{0.0f}},
		m_distance{0.0f}{}

	Intersection(glm::vec3 const&position, glm::vec3 const& direction, double const& distance):
		m_position{position},
		m_direction{direction},
		m_distance{distance}{}

	glm::vec3 getPosition(){ return this->m_position;}
	glm::vec3 getDirection(){ return this->m_direction;}
	double getDistance(){return this-> m_distance;}

};




#endif

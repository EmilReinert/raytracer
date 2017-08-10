#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <string>




class Intersection{
	glm::vec3 m_position;
	glm::vec3 m_direction;
	double m_distance;
	bool m_hit;


public:
	Intersection():
		m_position{glm::vec3{0.0f,0.0f,0.0f}},
		m_direction{glm::vec3{0.0f}},
		m_distance{0.0f},
		m_hit{false}{}

	Intersection(glm::vec3 const&position, glm::vec3 const& direction, double const& distance, bool const & hit):
		m_position{position},
		m_direction{direction},
		m_distance{distance},
		m_hit{hit}{}

	glm::vec3 const getPosition(){ return this->m_position;}
	glm::vec3 const getDirection(){ return this->m_direction;}
	double const getDistance(){return this-> m_distance;}
	bool const isHit(){return this->m_hit;}

};




#endif

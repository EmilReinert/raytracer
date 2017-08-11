
//ray struct

#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/vec3.hpp>
#include <cmath>



struct Ray
{
	glm::vec3 m_origin;
	glm::vec3 m_direction;
public:
	Ray():
		m_origin{glm::vec3{0.0f}},
		m_direction{glm::vec3{0.0f}}
		{}

	Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		m_origin{orig},
		m_direction{dir}
{}

	// << Output Operator
  	  friend std::ostream& operator<<(std::ostream& os, Ray const& ray)
   	 {
    	    os  << "\norigin: " << ray.m_origin.x << ", "
        	<< ray.m_origin.y <<", "
        	<< ray.m_origin.z
        	<< "\ndirection: " << ray.m_direction.x << ", "
        	<< ray.m_direction.y <<", "
        	<< ray.m_direction.z;
        return os;
    }
	//copy constructor
	Ray(Ray const& ray):m_origin{ray.m_origin},m_direction{ray.m_direction}{}
	//sets new direction
	void const setDirection(glm::vec3 const& dir){this->m_direction = dir; }
	//
	double const getLength(){ 
		float holder = (this->m_direction.x*this->m_direction.x)+
				(this->m_direction.y*this->m_direction.y)+
				(this->m_direction.z*this->m_direction.z);
		return sqrt(holder);}
	
};


#endif

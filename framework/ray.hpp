
//ray struct

#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>
#include "color.hpp"


struct Ray
{
	glm::vec3 m_origin;
	glm::vec3 m_direction;
public:
	Ray();

	Ray(glm::vec3 const& orig, glm::vec3 const& dir);

	// << Output Operator
  	  friend std::ostream& operator<<(std::ostream& os, Ray const& ray)
   	 {
    	    os <<"\nRay: \n" << "\norigin: " << ray.m_origin.x << ", "
        	<< ray.m_origin.y <<", "
        	<< ray.m_origin.z
        	<< "\ndirection: " << ray.m_direction.x << ", "
        	<< ray.m_direction.y <<", "
        	<< ray.m_direction.z;
        return os;
    }
	//copy constructor
	Ray(Ray const& ray);

	//sets new direction
	void const setDirection(glm::vec3 const& dir);

	//returns ray length
	double getLength() const;

	//returns new ray with length
	Ray newLength(double const& length)const;

	// returns float of ankle between two rays' directions
	float rayWinkel(glm::vec3 const& vec);

	//mirrors Ray on mirrorRay(both with same origin!) and returns that Ray
	Ray mirror(Ray const& mirrorRay) const;		
		
	//returns vector A with length of b projected on a 
	glm::vec3 BProjectOnA(glm::vec3 const&b,glm::vec3 const& a)const;

	//returns Inverse Direction
	glm::vec3 getInvDir()const;


	glm::vec3 crossproduct(glm::vec3 const& a,glm::vec3 const&b);


	float skalarProdukt(glm::vec3 const& a,glm::vec3 const&b);

	Color const raytrace();
	
	Ray const refractionRay(Ray const& mirror);
};





#endif

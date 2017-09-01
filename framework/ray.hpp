
//ray struct

#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include "color.hpp"
#include <glm/gtc/matrix_transform.hpp> 


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
	
	//retrurns Ray with transformed direction 
	Ray transformRay(glm::mat4 const & mat);
	
	
	glm::vec3 crossproduct(glm::vec3 const& a,glm::vec3 const&b);


	float skalarProdukt(glm::vec3 const& a,glm::vec3 const&b);

	Color const raytrace();
	
	Ray const reflectionRay(Ray const& mirror);
	
	Ray const refractionRay(Ray const& mirror);
};

glm::mat4 create_rotation( float const& angle, glm::vec3 axis);
glm::mat4 create_scalation ( float const x, float const y, float const z);
glm::mat4 create_translation( glm::vec3 const & vec);

#endif

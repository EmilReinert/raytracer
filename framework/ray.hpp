
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

	//returns ray length
	double const getLength(){ 
		float holder = (this->m_direction.x*this->m_direction.x)+
				(this->m_direction.y*this->m_direction.y)+
				(this->m_direction.z*this->m_direction.z);
		return sqrt(holder);}
	//returns new ray with length
	Ray newLength(double const& length){
		//glm::normalize doesnt work - > own implementation
		auto lngth = getLength();
		glm::vec3 normalDirection{m_direction.x/lngth,m_direction.y/lngth,m_direction.z/lngth};
		Ray rayy(m_origin,normalDirection);
		auto rayd = rayy.m_direction;
		glm::vec3 newdirection(length*rayd.x,length*rayd.y,length*rayd.y);
		rayy.setDirection(newdirection);
		return rayy;
	}

	// returns float of ankle between two rays' directions
	float rayWinkel(Ray const& ray2){ // x/y = |u*v|  /  |u|*|v| = cos(ß)
		// arccos = acos() // |u|= abs(u)
		auto u = this->m_direction;
		auto v = ray2.m_direction;
		//Skalarprodukt:
		auto x = abs((u.x*v.x)+(u.y*v.y)+(u.z*v.z));
		std::cout<<x;
		//unterm bruch
		auto y = (sqrt((u.x*u.x)+(u.y*u.y)+(u.z*u.z)) * sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z)));
		std::cout<<y;
		if (y==0){return -1;}
		std::cout<<(float)1/3;
		return acos(x/y)*(180/M_PI);
	}

		

	
};



#endif

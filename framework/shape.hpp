
//Interface for shapes

#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <material.hpp>
#include <iostream>

#include "ray.hpp"
#include <limits>
#include <math.h>  
#include <cmath>
#include <catch.hpp>


//For Intersect Methods
# include <glm/glm.hpp>
# include <glm/gtx/intersect.hpp>
struct Intersection;
class Shape
{
public:

	Shape(std::string const& name, Material const& material);

	virtual ~Shape();

	//pure virtual methods (no implementation in base class)
	virtual float area() const = 0;
	virtual float volume() const = 0;

	//virtual methods
	virtual std::string get_name() const; 
	virtual Material get_material() const;

	//fried -> should normally be outside the class, but uses Shape
	//member variables, therefore marked as friend and able to 
	//access members directly
	//the operator takes an shape object and calls the objects
	//default or custom print function
	friend std::ostream& operator<<(std::ostream& os, Shape const& s);

	virtual std::ostream& print (std::ostream& os) const;

	//both important for forming of Intersection
	virtual bool intersect(Ray const& ray, float& distance) = 0;
	virtual Intersection realintersect(Ray const& ray, float& distance) =0;
	
protected:
	std::string m_name;
	Material m_material;
};

#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <string>




struct Intersection{
	glm::vec3 m_position;
	glm::vec3 m_direction;
	double m_distance;
	bool m_hit;
	Shape* m_shape=nullptr;
	


public:
	Intersection():
		m_position{glm::vec3{0.0f,0.0f,0.0f}},
		m_direction{glm::vec3{0.0f}},
		m_distance{0.0f},
		m_hit{false},
		m_shape{nullptr}{}

	Intersection(glm::vec3 const&position, glm::vec3 const& direction, double const& distance, bool const & hit, Shape* const shape):
		m_position{position},
		m_direction{direction},
		m_distance{distance},
		m_hit{hit},
		m_shape{shape}{}

	glm::vec3 const getPosition(){ return this->m_position;}
	glm::vec3 const getDirection(){ return this->m_direction;}
	double const getDistance(){return this-> m_distance;}
	bool const isHit(){return this->m_hit;}
	Shape* getShape(){return this->m_shape;}

	//override INTERSECTION print
	std::ostream& print (std::ostream& os) const{
		os 	<< "\nHit?: "<<m_hit<<"\nDistance: "<<m_distance<<"\nHit-Shape: "<<m_shape->get_name()<<"\nPosition: "<< "(" << m_position.x << ", " <<m_position.y<< ", " <<m_position.z << ")"
		<< "\nDirection: " << "(" << m_direction.x << ", " << m_direction.y << ", " << m_direction.z << ")"
		<< "\n";
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, Intersection const& i)
{
    return i.print(os);
}


};
//<< for INTERSECTION





#endif
#endif //BUW_SHAPE_HPP

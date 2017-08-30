#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"
#include <string>



class Light{

	glm::vec3 m_source;
	float m_radius;
	std::string m_name;
	Color m_clr;
	float m_intensity;
public:
	Light():
		m_name{"noname_light"},m_source{0.0},m_clr{Color()},m_radius{0.0f}{}

	Light( std::string const& name,glm::vec3 const&source, Color const& clr):
		m_name{name},m_source{source},m_clr{clr}{}
	Light( std::string const& name,glm::vec3 const&source, float const& radius, Color const& clr):
		m_name{name},m_source{source},m_clr{clr},m_radius{radius}{}
	Light( std::string const& name,glm::vec3 const&source, float const& radius, Color const& clr, float const& intensity):
		m_name{name},m_source{source},m_clr{clr},m_radius{radius},m_intensity{intensity}{}

	glm::vec3  getSource()const{ return this->m_source;}
	std::string  getName()const{ return this->m_name;}
	Color  getColor()const{ return this->m_clr;}
	float getRadius()const{return this->m_radius;}
	float getIntensity()const{return this->m_intensity;}


	bool intersect(Ray const& ray, float& distance){
	auto normal_direction = glm::normalize(ray.m_direction);
	return glm::intersectRaySphere(
		ray.m_origin, normal_direction,
		m_source,
		m_radius * m_radius,distance);}




};

#endif

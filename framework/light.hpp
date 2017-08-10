#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"
#include <string>



class Light{

	glm::vec3 m_source;
	std::string m_name;
	Color m_clr;
public:
	Light():
		m_name{"noname_light"},m_source{0.0},m_clr{Color()}{}

	Light( std::string const& name,glm::vec3 const&source, Color const& clr):
		m_name{name},m_source{source},m_clr{clr}{}

	glm::vec3 getSource(){ return this->m_source;}
	std::string getName(){ return this->m_name;}
	Color getColor(){ return this->m_clr;}






};

#endif


//shape

#include "shape.hpp"

//Constructor
Shape::Shape (std::string const& name, Material const& material) :
	m_name{name},
	m_material{material}
{}

//Destructor
Shape::~Shape()
{}

//Getter
std::string Shape::get_name() const
{
	return m_name;
}

Material Shape::get_material() const
{
	return m_material;
}

std::ostream& Shape::print (std::ostream& os) const
{
	os  << "\nname:       " << m_name
		<< "\nmaterial:      " << m_material;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
    return s.print(os);
}

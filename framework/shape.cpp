
//shape

#include "shape.hpp"

//Constructor
Shape::Shape (std::string const& name, Material const& material) :
	m_name{name},
	m_material{material},
	m_transformation{glm::mat4(1.0f)}
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

void Shape::rotate( float const& angle, glm::vec3 axis){
	glm::mat4 mat = create_rotation(angle,axis);
	this->m_transformation=mat;
	}
void Shape::scale( float const x, float const y, float const z){
	glm::mat4 mat = create_scalation(x,y,z);
	this->m_transformation=mat;
	}
void Shape::translate( glm::vec3 const & vec){
	glm::mat4 mat = create_translation(-vec);
	this->m_transformation=mat;
	}






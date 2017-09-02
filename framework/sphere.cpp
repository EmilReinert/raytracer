
//sphere

#include "sphere.hpp"
#include <math.h>

//default constructor unit sphere
Sphere::Sphere(std::string const& name) :
	Shape{name,
		  Material{"sphere_material", Color{0.0f,0.0f,0.0f},
				Color{0.0f,0.0f,0.0f},
				Color{0.0f,0.0f,0.0f},
				0.0f}},
	m_center{glm::vec3{0.0f}},
	m_radius{1}
{}

//custom constructor
Sphere::Sphere(std::string const& name, Material const& material,
	glm::vec3 const& center, float radius) :
	
	Shape{name,material},
	m_center{center},
	m_radius{radius}{}

//dtor
Sphere::~Sphere(){}

//getter
glm::vec3 const& Sphere::get_center() const
{
	return m_center;
}

float const& Sphere::get_radius() const
{
	return m_radius;
}

//override area
float Sphere::area () const
{
	return 4*M_PI*m_radius*m_radius;
}

//override volume
float Sphere::volume () const
{
	return (4.0f/3.0f)*M_PI*pow(m_radius,3.0f);
}

//override print
std::ostream& Sphere::print (std::ostream& os) const
{
	os 	<< "\nshape type: sphere";
	//uses the default shape parent implementation of print on this instance
	//to print name and material
	Shape::print(os); //prints name and material
	os	<<   "center:     " << "(" << m_center.x << ", " << m_center.y << ", " << m_center.z << ")"
		<< "\nradius:     " << m_radius
		<< "\n";
	return os;
}
//returns if theres an intersection btwn Sphere & Ray
bool Sphere::intersect(Ray const& ray, float& distance)const
{
	auto normal_direction = glm::normalize(ray.m_direction);
	return glm::intersectRaySphere(
		ray.m_origin, normal_direction,
		m_center,
		m_radius * m_radius,distance);
}
//returns the intersection btwn Sphere & Ray
Intersection Sphere::realintersect(Ray const& ray1, float& distance){
	Intersection inter = Intersection();
	//is there even an intersection
	float holder = distance;
	Ray rr =ray1;
	Ray ray = rr.transformRay(m_transformation);
	
	bool hit = intersect(ray,holder);
	if( !hit){return inter;}
	//geometrie
	auto a = glm::normalize(ray.m_direction);
	auto b = m_center-ray.m_origin;//ray origin to center
	float b_length = sqrt((b.x*b.x)+(b.y*b.y)+(b.z*b.z));
	float sklr = a.x*b.x+a.y*b.y+a.z*b.z;//a°b
	float lng = a.x*a.x+a.y*a.y+a.z*a.z ;// |a|*|a|
	float fktr = sklr / lng;
	glm::vec3 c{a.x*fktr,a.y*fktr,a.z*fktr}; // b projected on a (ray-direction)
	float c_length = sqrt((c.x*c.x)+(c.y*c.y)+(c.z*c.z));
	float d_length =sqrt(abs((b_length*b_length)-(c_length*c_length)));//midperpendicular to ray-direction //b_length²-c_length² = d_length²
	float e_length = sqrt((m_radius*m_radius)-(d_length*d_length));
	float dis =c_length-e_length;
	inter.m_distance = dis;
	inter.m_hit = true;
	inter.m_shape = std::make_shared<Sphere>(*this);
	inter.m_position= ray.m_origin+glm::vec3{dis*a.x,dis*a.y,dis*a.z};
	
	inter.m_normal = inter.m_position-m_center;

	return inter;
	

}

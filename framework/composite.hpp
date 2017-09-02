#ifndef BUW_COMPOSITE_HPP
#define  BUW_COMPOSITE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Composite : public Shape
{
public:
	//default constructor unit sphere
	Composite();

	//custom constructor
	Composite(std::string const&name);

	//override dtor
	~Composite();
	
	//override area
	float area () const override;

	//override volume
	float volume () const override;

	//override print
	std::ostream& print (std::ostream& os) const override;

	bool intersect(Ray const& ray, float& distance)const override;
	Intersection realintersect(Ray const& ray1, float& distance) override;

	//adding and removing components
	void add_shape(std::shared_ptr<Shape> const & shape);
	void rm_shape(std::shared_ptr<Shape> const & shape);




	std::vector<std::shared_ptr<Shape>> m_components;
};

#endif 

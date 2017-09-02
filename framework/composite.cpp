#include "composite.hpp"


//default constructor unit sphere
	Composite::Composite():
		Shape{"default_comp",{}},
		m_components{}{}

	//custom constructor
	Composite::Composite(std::string const&name):
		Shape{name,{}},
		m_components{}{}
	

	//override dtor
	Composite::~Composite(){}

	//override print
	std::ostream& Composite::print (std::ostream& os) const{
		os<<"\nComposite:";
		if(m_components.empty()){os<<"\n----contains no shapes yet----\n";}
		else{
			int i = 1;
			for(std::shared_ptr<Shape> shp: m_components){
				os<<"\nShape "<<i<<": "<< shp->get_name();
				i++;}}
		return os;
	}
	bool Composite::intersect(Ray const& ray, float& distance)const{return false;}

	Intersection Composite::realintersect(Ray const& ray1, float& distance){
		if(m_components.empty()){return Intersection();}
		float distance_to_object = 10000000000000000;
		std::shared_ptr<Shape> shape_ptr;
		Intersection i;
		for(std::shared_ptr<Shape> shp: m_components){ 
			Intersection inter = shp->realintersect(ray1,distance);
			if(inter.isHit()&&inter.getDistance()< distance_to_object){//&&inter.getShape()!=shp){
				shape_ptr = inter.getShape();
				distance_to_object = inter.getDistance();
				i = inter;
			
			}
		}
		return i;
	}
	
		//override area
	float Composite::area () const{return 0;}

	//override volume
	float Composite::volume () const {return 0;}


	
	//adding and removing components
	void Composite::add_shape(std::shared_ptr<Shape> const & shape){
		m_components.push_back(shape);
	}
	void Composite::rm_shape(std::shared_ptr<Shape> const & shape){
		 m_components.erase(std::remove(m_components.begin(), m_components.end(), shape), m_components.end());
	}





//box

#include "box.hpp"


//default constructor unit box
Box::Box(std::string const& name) :
	Shape{name, Material{"box_material", Color{0.0f,0.0f,0.0f},
						Color{0.0f,0.0f,0.0f},
						Color{0.0f,0.0f,0.0f},
						0.0f}},
	m_min{glm::vec3{0.0f}},
	m_max{glm::vec3{1.0f}}
{}

//custom constructor
Box::Box(std::string const& name, Material const& material,
	glm::vec3 const& min, glm::vec3 const& max) :
	
	Shape{name, material},
	m_min{min},
	m_max{max}
{
	sortMinMax();
}

void Box::sortMinMax()
{
	if(m_min.x > m_max.x)
	{
		float buffer = m_min.x;
		m_min.x = m_max.x;
		m_max.x = buffer;
	}
	
	if(m_min.y > m_max.y)
	{
		float buffer = m_min.y;
		m_min.y = m_max.y;
		m_max.y = buffer;
	}
	
	if(m_min.z > m_max.z)
	{
		float buffer = m_min.z;
		m_min.z = m_max.z;
		m_max.z = buffer;
	}
}

//getter
glm::vec3 const& Box::get_min() const
{
	return m_min;
}

glm::vec3 const& Box::get_max() const
{
	return m_max;
}

//override area
float Box::area () const
{
	auto diff = m_max - m_min;
	return diff.x * diff.y * 2 + diff.x * diff.z * 2+ diff.y * diff.z * 2;
}

//override volume
float Box::volume () const
{
	auto diff = m_max - m_min;
	return diff.x * diff.y * diff.z;
}

//override print
std::ostream& Box::print (std::ostream& os) const
{
	os 	<< "\nshape type: box";
	//uses the default shape parent implementation of print on this instance
	//to print name and material
	Shape::print(os); //prints name and material
	os	<<   "min:        " << "(" << m_min.x << ", " << m_min.y << ", " << m_min.z << ")"
		<< "\nmax:        " << "(" << m_max.x << ", " << m_max.y << ", " << m_max.z << ")"
		<< "\n";
	return os;
}



//override intersect
bool Box::intersect(Ray const& ray, float& distance)const
{
	  Ray nray {ray.m_origin,ray.m_direction};
    nray.m_direction = glm::normalize(ray.m_direction);

    glm::vec3 invers = nray.getInvDir();

    float t0 = (m_min.x - nray.m_origin.x) * invers.x;
    float t1 = (m_max.x - nray.m_origin.x) * invers.x;
    float tmin = std::min(t0, t1);
    float tmax = std::max(t0, t1);
    

    t0 = (m_min.y - nray.m_origin.y) * invers.y;
    t1 = (m_max.y - nray.m_origin.y) * invers.y;
    tmin = std::max(tmin, std::min(t0, t1));
    tmax = std::min(tmax, std::max(t0, t1));
    

    t0 = (m_min.z - nray.m_origin.z) * invers.z;
    t1 = (m_max.z - nray.m_origin.z) * invers.z;
    tmin = std::max(tmin, std::min(t0, t1));
    tmax = std::min(tmax, std::max(t0, t1));
    
    if(tmax > std::max(tmin, 0.0f))
{return true;}
	return false;
}


//Returns intersect as Intersection
Intersection Box::realintersect(Ray const& ray, float& distance){ 
	Intersection iii = Intersection();
    //normalize ray
	   
    Ray noray {ray.m_origin,ray.m_direction};
    noray.m_direction = glm::normalize(ray.m_direction);
    Ray nray = noray.transformRay(m_transformation);
    glm::vec3 invers = nray.getInvDir();

    float t0 = (m_min.x - nray.m_origin.x) * invers.x;
    float t1 = (m_max.x - nray.m_origin.x) * invers.x;
    float tmin = std::min(t0, t1);
    float tmax = std::max(t0, t1);
    

    t0 = (m_min.y - nray.m_origin.y) * invers.y;
    t1 = (m_max.y - nray.m_origin.y) * invers.y;
    tmin = std::max(tmin, std::min(t0, t1));
    tmax = std::min(tmax, std::max(t0, t1));
    

    t0 = (m_min.z - nray.m_origin.z) * invers.z;
    t1 = (m_max.z - nray.m_origin.z) * invers.z;
    tmin = std::max(tmin, std::min(t0, t1));
    tmax = std::min(tmax, std::max(t0, t1));
    
    if(tmax > std::max(tmin, 0.0f))
{
	iii.m_hit = true;
	  iii.m_distance = sqrt(tmin * tmin *
                (nray.m_direction.x * nray.m_direction.x + 
                nray.m_direction.y * nray.m_direction.y + 
                nray.m_direction.z * nray.m_direction.z));
	iii.m_shape = std::make_shared<Box>(*this);
       iii.m_position = glm::vec3{ray.m_origin.x + iii.m_distance * nray.m_direction.x,
            ray.m_origin.y + iii.m_distance * nray.m_direction.y,
            ray.m_origin.z + iii.m_distance * nray.m_direction.z};
       
	//on the search for the given plane - normal vector for mirrorVec
	glm::vec3 n{0.0f};
	if((iii.m_position.x) == Approx(m_min.x))
        {
           n = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        else if((iii.m_position.x) == Approx(m_max.x))
        {
            n = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        else if((iii.m_position.y) == Approx(m_min.y))
        {
            n = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        else if((iii.m_position.y) == Approx(m_max.y))
        {
            n = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        else if((iii.m_position.z) == Approx(m_min.z))
        {
            n = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        else if((iii.m_position.z) == Approx(m_max.z))
        {
            n = glm::vec3{0.0f, 0.0f, 1.0f};
        }

	iii.m_normal = n;
	}
	/*
        if((hit.m_position.x) == Approx(m_min.x))
        {
           hit.m_normale = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        else if((hit.m_position.x) == Approx(m_max.x))
        {
            hit.m_normale = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        else if((hit.m_position.y) == Approx(m_min.y))
        {
            hit.m_normale = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        else if((hit.m_position.y) == Approx(m_max.y))
        {
            hit.m_normale = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        else if((hit.m_position.z) == Approx(m_min.z))
        {
            hit.m_normale = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        else if((hit.m_intersection.z) == Approx(m_max.z))
        {
            hit.m_normale = glm::vec3{0.0f, 0.0f, 1.0f};
        }*/
	
	return iii;
	
}





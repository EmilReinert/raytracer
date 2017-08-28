
//ray struct


#include <glm/vec3.hpp>
#include <cmath>
#include "ray.hpp"


	Ray::Ray():
		m_origin{glm::vec3{0.0f}},
		m_direction{glm::vec3{0.0f}}
		{}

	Ray::Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		m_origin{orig},
		m_direction{dir}
{}


	//copy constructor
	Ray::Ray(Ray const& ray):m_origin{ray.m_origin},m_direction{ray.m_direction}{}

	//sets new direction
	void const Ray::setDirection(glm::vec3 const& dir){this->m_direction = dir; }

	//returns ray length
	double Ray::getLength() const { 
		float holder = (this->m_direction.x*this->m_direction.x)+
				(this->m_direction.y*this->m_direction.y)+
				(this->m_direction.z*this->m_direction.z);
		return sqrt(holder);}
	//returns new ray with length
	Ray Ray::newLength(double const& length)const{
		//glm::normalize doesnt work - > own implementation
		auto lngth = getLength();
		glm::vec3 normalDirection{m_direction.x/lngth,m_direction.y/lngth,m_direction.z/lngth};
		Ray rayy(m_origin,normalDirection);
		return rayy;
	}

	// returns float of ankle between two rays' directions
	float Ray::rayWinkel(glm::vec3 const& vec){ // x/y = |u*v|  /  |u|*|v| = cos(ß)
		// arccos = acos() // |u|= abs(u)
		auto u = this->m_direction;
		auto v = vec;
		//Skalarprodukt:
		auto x = (u.x*v.x)+(u.y*v.y)+(u.z*v.z);
		x =abs(x);
		//unterm bruch
		auto y = sqrt((u.x*u.x)+(u.y*u.y)+(u.z*u.z)) * sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
		
		if (y==0){return -1;}
		
		return acos(x/y)*(180/M_PI);
	}

	//mirrors Ray on mirrorRay(both with same origin!) and returns that Ray
	Ray Ray::mirror(Ray const& mirrorRay) const{
		if(mirrorRay.m_direction==glm::vec3{0.0f}||m_direction==glm::vec3{0.0f}){return Ray{glm::vec3{0.0f},glm::vec3{0.0f}};}
		/*//Hilfsebene:
		glm::vec3 v = crossproduct(m_direction,mirrorRay.m_direction);
		glm::vec3 n = crossproduct(v,mirrorRay.m_direction); //Normalvector
			//Normalengleichung
		float ende = (n.x*m_origin.x)+(n.y*m_origin.y)+(n.y*m_origin.y);
		//Hilfsgerade O+ß*n
		//Schnittpunkt*/
		
		glm::vec3 mid = BProjectOnA(m_direction,mirrorRay.m_direction);
		auto pointS = mid-m_origin;
		auto pointP = m_direction-m_origin;
		auto PS = pointS-pointP;
		auto P_ = PS+pointS;
		return Ray{m_origin,P_-m_origin}.newLength(1);
		}
		
		
	//returns vector A with length of b projected on a 
	glm::vec3 Ray::BProjectOnA(glm::vec3 const&b,glm::vec3 const& a)const{
		Ray r = {m_origin,a};
		float b_length = sqrt((b.x*b.x)+(b.y*b.y)+(b.z*b.z));
		if(r.rayWinkel(b)==90){return glm::vec3(0.0f);}
		float ccc = cos(r.rayWinkel(b)/(180/M_PI));
		//std::cout<<r.rayWinkel(b);
		float fktr = ccc*b_length;
		
		Ray ad = r.newLength(1);
		return glm::vec3{ad.m_direction.x*fktr,ad.m_direction.y*fktr,ad.m_direction.z*fktr}; }


	glm::vec3 Ray::crossproduct(glm::vec3 const& a,glm::vec3 const&b){
		return glm::vec3{a.y*b.z-a.z*b.y,a.z*b.x-a.x-b.z,a.x*b.y-a.y*b.x};}

	float skalarProdukt(glm::vec3 const& a,glm::vec3 const&b){return a.x*b.x+a.y+b.y+a.z*b.z;}

	glm::vec3 Ray::getInvDir()const{float xx,yy,zz;
		if(m_direction.x==0){xx=0;}else{xx=1/m_direction.x;}
		if(m_direction.y==0){yy=0;}else{yy=1/m_direction.y;}
		if(m_direction.z==0){zz=0;}else{zz=1/m_direction.z;}
		return glm::vec3{xx,yy,zz};}

	Color const Ray::raytrace(){return Color{0.0,1.0,1.0};}

	Ray const Ray::refractionRay(Ray const& mirror){
		int eta = 1;
		glm::vec3 direction =glm::vec3(0.0f);
		glm::vec3 N = mirror.m_direction;
		glm::vec3 I = m_direction;
		float k = 1.0-eta*eta*(1.0-(((N.x*I.x)+(N.y*I.y)+(N.z*I.z))*((N.x*I.x)+(N.y*I.y)+(N.z*I.z))));
		if(k>=0.0){
			direction = glm::vec3{eta*I.x,eta*I.y,eta*I.z}-glm::vec3{(eta*((N.x*I.x)+(N.y*I.y)+(N.z*I.z))+sqrt(k))*N.x,(eta*((N.x*I.x)+(N.y*I.y)+(N.z*I.z))+sqrt(k))*N.y,(eta*((N.x*I.x)+(N.y*I.y)+(N.z*I.z))+sqrt(k))*N.z};
		}

		return Ray{m_origin,direction};}





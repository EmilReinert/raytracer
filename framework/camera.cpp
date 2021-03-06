#include "camera.hpp"


	Camera::Camera():
		m_name{"camera_default"},
		m_fov{60},
		m_position{glm::vec3{0.0f}},
		m_direction{glm::vec3{0.0f,0.0f,-1.0f}},
		m_up{glm::vec3{0.0f,1.0f,0.0f}},
		m_transformation{glm::mat4(1.0f)}{}

	Camera::Camera(std::string const& name, unsigned const&fov):
		m_name{name},
		m_fov{fov},
		m_position{glm::vec3{0.0f}},
		m_direction{glm::vec3{0.0f,0.0f,-1.0f}},
		m_up{glm::vec3{0.0f,1.0f,0.0f}},
		m_transformation{glm::mat4(1.0f)}{}


	Camera::Camera(std::string const& name, unsigned const&fov,glm::vec3 const&position,glm::vec3 const&direction,glm::vec3 const &up):
		m_name{name},
		m_fov{fov},
		m_position{position},
		m_direction{direction},
		m_up{glm::vec3{up}},
		m_transformation{glm::mat4(1.0f)}{}
	
		Camera::Camera(std::string const& name, unsigned const&fov,glm::vec3 const&position,glm::vec3 const&direction,glm::vec3 const & up,glm::mat4 const& trans):
		m_name{name},
		m_fov{fov},
		m_position{position},
		m_direction{direction},
		m_up{glm::vec3{up}},
		m_transformation{trans}{}
	






	//getter
	std::string Camera::getName() const{return this-> m_name;}
	unsigned Camera::getFov() const{return this-> m_fov;}
	glm::vec3 Camera::getPosition() const{return this-> m_position;}
	glm::vec3 Camera::getDirection() const{return this-> m_direction;}
	glm::vec3 Camera::getUp() const{return this-> m_up;}

	//retuns Ray which directis do a certain Pixel starting at camera.m_position
	Ray Camera::castRay(int x, int y, int resolution_x, int resolution_y )const{
		float dis_film = (0.5 / tan(m_fov/2));

 		 float xx = float(x) * 1.0 / float(resolution_x) - 0.5;
  		float yy = float(y) * 1.0 / float(resolution_y) - 0.5;
  		float zz = -1.0 * dis_film;

 		 glm::vec3 direction{xx,yy,zz}; 
  		
  
		Ray ray = Ray{m_position, direction}.newLength(1);
		Ray transformed = ray.transformRay(m_transformation);
		return transformed;
		/*
		float zz = -120;
		float xx,yy;
		if(x>=(resolution_x/2)){
			xx = x-resolution_x/2;}
		else{
			xx = -1*((resolution_x/2)-x);//std::cout<<"-"<<resolution_x<<"-"<<x<<"-"<<xx<<"-";
}
		if(y>=(resolution_y/2)){
			yy = y-resolution_y/2;}
		else{
			yy = -1*((resolution_y/2)-y);//std::cout<<"-"<<resolution_y<<"-"<<y<<"-"<<yy<<"-";
}
		glm::vec3 ray_direction{xx,yy,zz};
		return Ray{m_position,ray_direction};*/


	}













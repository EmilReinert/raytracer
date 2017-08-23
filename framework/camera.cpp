#include "camera.hpp"


	Camera::Camera():
		m_name{"camera_default"},
		m_fov{90},
		m_position{glm::vec3{0.0f}},
		m_direction{glm::vec3{0.0f,0.0f,-1.0f}},
		m_up{glm::vec3{0.0f,1.0f,0.0f}}{}

	Camera::Camera(std::string const& name, unsigned const&fov):
		m_name{name},
		m_fov{fov},
		m_position{glm::vec3{0.0f}},
		m_direction{glm::vec3{0.0f,0.0f,-1.0f}},
		m_up{glm::vec3{0.0f,1.0f,0.0f}}{}


	Camera::Camera(std::string const& name, unsigned const&fov,glm::vec3 const&position,glm::vec3 const&direction,glm::vec3 up):
		m_name{name},
		m_fov{fov},
		m_position{position},
		m_direction{direction},
		m_up{glm::vec3{up}}{}




	//getter
	std::string Camera::getName() const{return this-> m_name;}
	unsigned Camera::getFov() const{return this-> m_fov;}
	glm::vec3 Camera::getPosition() const{return this-> m_position;}
	glm::vec3 Camera::getDirection() const{return this-> m_direction;}
	glm::vec3 Camera::getUp() const{return this-> m_up;}

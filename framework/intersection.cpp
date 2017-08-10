#include "intersection.hpp"
#include <iostream>
#include <glm/vec3.hpp>
#include <string>
#include <cmath>


Intersection::Intersection():
	m_position{nullptr},
	m_direction{glm::vec3(INFINITY,INFINITY,INFINITY)},
	m_distance{INFINITY}{}

Intersection::Intersection(glm::vec3 const&position, glm::vec3 const& direction, float const& distance)
	m_position{position},
	m_direction{direction},
	m_distance{distance}{}

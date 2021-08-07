#ifndef PLACEBLE_OBJECT_H
#define PLACEBLE_OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Placeble_object {
	Placeble_object(glm::vec3 a_location) :
		location{ a_location }
	{}

	glm::vec3 location;
};

#endif
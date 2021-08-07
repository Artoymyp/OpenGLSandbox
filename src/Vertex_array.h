#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Vertex_array {
	Vertex_array(glm::vec3 a_location) :
		location{ a_location }
	{}

	glm::vec3 location;
};

#endif
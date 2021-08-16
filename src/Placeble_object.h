#ifndef PLACEBLE_OBJECT_H
#define PLACEBLE_OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Texture.h>


struct Placeble_object {
	Placeble_object(glm::vec3 a_location, Texture* a_texture) :
		location{ a_location },
		texture{a_texture}
	{}

	glm::vec3 location;
	Texture* texture;
};

#endif
#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"

struct Face {
	Face(Vertex vertex_0, Vertex vertex_1, Vertex vertex_2) :
		v0{ vertex_0 },
		v1{ vertex_1 },
		v2{ vertex_2 }
	{

	}

	Vertex v0;
	Vertex v1;
	Vertex v2;

	friend bool operator==(const Face& lh, const Face& rh) {
		return
			lh.v0 == rh.v0 &&
			lh.v1 == rh.v1 &&
			lh.v2 == rh.v2;
	}
	
	Face operator+(glm::vec3 vec) const {
		return Face{v0 + vec, v1 + vec, v2 + vec};
	}

	friend bool operator!=(const Face& lh, const Face& rh) {
		return !(lh == rh);
	}
};
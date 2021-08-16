#ifndef VERTEX_H
#define VERTEX_H
#include <glm/glm.hpp>

const float Tolerance{ 0.00001f };

inline bool tol_eq(float lh, float rh) {
	return std::abs(lh - rh) < Tolerance;
};

struct Vertex {
	Vertex(float x_coord, float y_coord, float z_coord, float texture_u_coord, float texture_v_coord) :
		x{ x_coord },
		y{ y_coord },
		z{ z_coord },
		u{ texture_u_coord },
		v{ texture_v_coord }
	{}

	float x;
	float y;
	float z;

	// Texture coordinates
	float u;
	float v;

	Vertex operator+(glm::vec3 vec) const {
		return Vertex{ x + vec.x, y + vec.y, z + vec.z, u, v };
	}

	friend bool operator==(const Vertex& lh, const Vertex& rh){
		return
			tol_eq(lh.x, rh.x) &&
			tol_eq(lh.y, rh.y) &&
			tol_eq(lh.z, rh.z) &&
			tol_eq(lh.u, rh.u) &&
			tol_eq(lh.v, rh.v);
	}

	friend bool operator!=(const Vertex& lh, const Vertex& rh) {
		return !(lh == rh);
	}
};

#endif
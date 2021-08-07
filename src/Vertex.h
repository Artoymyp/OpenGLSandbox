#ifndef VERTEX_H
#define VERTEX_H

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
};

#endif
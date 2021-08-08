#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Placeble_object.h"


struct Vertex_array {
	Vertex_array()
	{
		glGenVertexArrays(1, &_id);
	}

	~Vertex_array() {
		glDeleteVertexArrays(1, &_id);
		if (_vbo) {
			glDeleteBuffers(1, &_vbo);
		}
	}

	unsigned int _id{ 0 };
	unsigned int _vbo{ 0 };
	unsigned int _vertices_count{ 0 };
	std::vector<const Placeble_object*> objects;

	void activate() {
		glBindVertexArray(_id);
	}

	void set_vertices(const std::vector<Vertex>& vertices) {
		if (_vbo) {
			throw std::exception("Vertices were already set.");
		}
		_vertices_count = vertices.size();

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, _vertices_count * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void set_model_to(const Placeble_object& object) {
		objects.push_back(&object);
	}

	void set_model_to(const std::vector<Placeble_object>& objects) {
		for each(auto& object in objects) 
		{
			set_model_to(object);
		}
		
	}

	void draw() {
		glDrawArrays(GL_TRIANGLES, 0, _vertices_count);
	}

};

#endif
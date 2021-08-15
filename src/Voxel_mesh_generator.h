#pragma once
#include <vector>
#include "Voxel_chunk.h"
#include "World.h"
#include <Face.h>


struct Voxel_mesh_generator {
	inline static Face top1_face{
		Vertex{0, 1, 0, 0, 0},
		Vertex{1, 1, 1, 1, 1},
		Vertex{0, 1, 1, 0, 1},
	};
	inline static Face top2_face{
		Vertex{0, 1, 0, 0, 0},
		Vertex{1, 1, 0, 1, 0},
		Vertex{1, 1, 1, 1, 1},
	};

	inline static Face bottom1_face{
		Vertex{0, 0, 1, 0, 0},
		Vertex{1, 0, 0, 1, 1},
		Vertex{0, 0, 0, 0, 1},
	};
	inline static Face bottom2_face{
		Vertex{0, 0, 1, 0, 0},
		Vertex{1, 0, 1, 1, 0},
		Vertex{1, 0, 0, 1, 1},
	};

	inline static Face back1_face{
		Vertex{1, 0, 1, 0, 0},
		Vertex{0, 1, 1, 1, 1},
		Vertex{1, 1, 1, 0, 1},
	};
	inline static Face back2_face{
		Vertex{1, 0, 1, 0, 0},
		Vertex{0, 0, 1, 1, 0},
		Vertex{0, 1, 1, 1, 1},
	};

	inline static Face front1_face{
		Vertex{0, 0, 0, 0, 0},
		Vertex{1, 1, 0, 1, 1},
		Vertex{0, 1, 0, 0, 1},
	};
	inline static Face front2_face{
		Vertex{0, 0, 0, 0, 0},
		Vertex{1, 0, 0, 1, 0},
		Vertex{1, 1, 0, 1, 1},
	};

	inline static Face right1_face{
		Vertex{1, 0, 0, 0, 0},
		Vertex{1, 1, 1, 1, 1},
		Vertex{1, 1, 0, 0, 1},
	};
	inline static Face right2_face{
		Vertex{1, 0, 0, 0, 0},
		Vertex{1, 0, 1, 1, 0},
		Vertex{1, 1, 1, 1, 1},
	};

	inline static Face left1_face{
		Vertex{0, 0, 1, 0, 0},
		Vertex{0, 1, 0, 1, 1},
		Vertex{0, 1, 1, 0, 1},
	};
	inline static Face left2_face{
		Vertex{0, 0, 1, 0, 0},
		Vertex{0, 0, 0, 1, 0},
		Vertex{0, 1, 0, 1, 1},
	};

	[[nodiscard]] static std::vector<Face> generate(unsigned int x, unsigned int z, World& w);
};
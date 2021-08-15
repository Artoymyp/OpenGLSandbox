#pragma once
#include <map>
#include "Voxel_chunk.h"

class World {
	std::map<int, std::map<int, Voxel_chunk>> _chunks;

public:
	World() {

	}

	Voxel_chunk& get_chunk(int x, int y) {
		return _chunks[x][y];
	}

	void set_chunk(int x, int y, Voxel_chunk chunk) {
		_chunks[x][y] = chunk;
	}
};
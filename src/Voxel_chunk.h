#pragma once
#include <algorithm>

enum class Voxel_type {
	Air = 0,
	Stone,
	Grass,
};

struct Voxel_chunk {
	Voxel_chunk(unsigned short chunk_width = 16, unsigned short chunk_height = 128) :
		width{ chunk_width },
		height{ chunk_height },
		blocks{ std::vector(width * width * height, Voxel_type::Air) }
	{

	}

	Voxel_type get_block(unsigned int x, unsigned int elevation, unsigned int z) const {
		return blocks[x + z * width + elevation * width * width];
	}

	void set_block(unsigned int x, unsigned int elevation, unsigned int z, Voxel_type type) {
		blocks[x + z * width + elevation * width * width] = type;
	}

	void set_layer(unsigned int elevation, Voxel_type type) {
		for (size_t x = 0; x < width; x++)
		{
			for (size_t z = 0; z < width; z++)
			{
				set_block(x, elevation, z, type);
			}
		}
	}

	unsigned short width;
	unsigned short height;
	std::vector<Voxel_type> blocks;
};

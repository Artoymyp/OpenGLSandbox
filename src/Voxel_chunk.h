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

	void set_region(
		unsigned int x1, 
		unsigned int x2, 
		unsigned int z1, 
		unsigned int z2, 
		unsigned int elevation1, 
		unsigned int elevation2,
		Voxel_type type) {
		for (size_t x = x1; x <= x2; x++)
		{
			for (size_t z = z1; z <= z2; z++)
			{
				for (size_t elevation = elevation1; elevation <= elevation2; elevation++) {
					set_block(x, elevation, z, type);
				}
			}
		}
	}

	void set_tree(unsigned int x, unsigned int elevation, unsigned int z) {
		set_block(x, elevation, z, Voxel_type::Stone);
		set_block(x, elevation + 1, z, Voxel_type::Stone);
		set_block(x, elevation + 2, z, Voxel_type::Stone);
		set_region(x - 1, x + 1, z - 1, z + 1, elevation + 3, elevation + 4, Voxel_type::Grass);
		set_block(x, elevation + 5, z, Voxel_type::Grass);
	}

	unsigned short width;
	unsigned short height;
	std::vector<Voxel_type> blocks;
};

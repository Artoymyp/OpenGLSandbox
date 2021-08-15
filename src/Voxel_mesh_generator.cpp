#include "Voxel_mesh_generator.h"

using glm::vec3;

std::vector<Face> Voxel_mesh_generator::generate(unsigned int x, unsigned int z, World& w)
{
	std::vector<Face> result;

	auto chunk = w.get_chunk(x, z);
	for (unsigned int elevation = 0; elevation < chunk.height - 1; elevation++) {
		for (unsigned int x = 0; x < chunk.width; x++) {
			for (unsigned int z = 0; z < chunk.width; z++) {
				vec3 displacement{ x, elevation, z };
				
				if (chunk.get_block(x, elevation, z) != Voxel_type::Air) {
					if (x > 0 && chunk.get_block(x - 1, elevation, z) == Voxel_type::Air) {
						result.emplace_back(left1_face + displacement);
						result.emplace_back(left2_face + displacement);
					}
					if (x < chunk.width - 1 && chunk.get_block(x + 1, elevation, z) == Voxel_type::Air) {
						result.emplace_back(right1_face + displacement);
						result.emplace_back(right2_face + displacement);
					}

					if (z > 0 && chunk.get_block(x, elevation, z - 1) == Voxel_type::Air) {
						result.emplace_back(front1_face + displacement);
						result.emplace_back(front2_face + displacement);
					}
					if (z < chunk.width - 1 && chunk.get_block(x, elevation, z + 1) == Voxel_type::Air) {
						result.emplace_back(back1_face + displacement);
						result.emplace_back(back2_face + displacement);
					}
					
					if (elevation > 0 && chunk.get_block(x, elevation - 1, z) == Voxel_type::Air) {
						result.emplace_back(bottom1_face + displacement);
						result.emplace_back(bottom2_face + displacement);
					}
					if (elevation < chunk.height - 1 && chunk.get_block(x, elevation + 1, z) == Voxel_type::Air) {
						result.emplace_back(top1_face + displacement);
						result.emplace_back(top2_face + displacement);
					}
				}
			}
		}
	}

	return result;
}

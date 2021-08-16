#include "Voxel_mesh_generator.h"

using glm::vec3;

void add_to_result(std::map<Voxel_type, std::vector<Face>>& result, Voxel_type type, const std::vector<Face>& faces, const vec3& displacement) {
	if (const auto it{ result.find(type) }; it == result.end()) {
		std::vector<Face> transformed_faces;
		for each (auto face in faces)
		{
			transformed_faces.push_back(face + displacement);
		}
		result.insert({ type, transformed_faces });
	}
	else {
		for each (auto face in faces)
		{
			it->second.push_back(face + displacement);
		}
	}

}

std::map<Voxel_type, std::vector<Face>> Voxel_mesh_generator::generate(unsigned int x, unsigned int z, World& w)
{
	std::map<Voxel_type, std::vector<Face>> result;

	auto chunk = w.get_chunk(x, z);
	for (unsigned int elevation = 0; elevation < chunk.height - 1; elevation++) {
		for (unsigned int x = 0; x < chunk.width; x++) {
			for (unsigned int z = 0; z < chunk.width; z++) {
				vec3 displacement{ x, elevation, z };
				
				if (auto type{ chunk.get_block(x, elevation, z) }; type != Voxel_type::Air) {
					if (x > 0 && chunk.get_block(x - 1, elevation, z) == Voxel_type::Air) {
						add_to_result(result, type, left_faces, displacement);
					}
					if (x < chunk.width - 1 && chunk.get_block(x + 1, elevation, z) == Voxel_type::Air) {
						add_to_result(result, type, right_faces, displacement);
					}

					if (z > 0 && chunk.get_block(x, elevation, z - 1) == Voxel_type::Air) {
						add_to_result(result, type, front_faces, displacement);
					}
					if (z < chunk.width - 1 && chunk.get_block(x, elevation, z + 1) == Voxel_type::Air) {
						add_to_result(result, type, back_faces, displacement);
					}
					
					if (elevation > 0 && chunk.get_block(x, elevation - 1, z) == Voxel_type::Air) {
						add_to_result(result, type, bottom_faces, displacement);
					}
					if (elevation < chunk.height - 1 && chunk.get_block(x, elevation + 1, z) == Voxel_type::Air) {
						add_to_result(result, type, top_faces, displacement);
					}
				}
			}
		}
	}

	return result;
}

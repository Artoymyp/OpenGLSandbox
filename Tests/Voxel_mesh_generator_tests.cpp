#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Voxel_mesh_generator.h"
#include <Vertex.h>
#include <Face.h>
#include <World.h>


using glm::vec3;

std::ostream& operator<<(std::ostream& os, const Vertex& bar) {
	return os << "{" << bar.x << ", " << bar.y << ", " << bar.z << "}";
}

std::ostream& operator<<(std::ostream& os, const Face& bar) {
	return os << "{" << bar.v0 << ", " << bar.v1 << ", " << bar.v2 << "}";
}

struct VoxelMeshGeneratorTests : public ::testing::Test {
	World create_world_with_single_chunk(Voxel_chunk chunk) {
		World w;
		w.set_chunk(0, 0, chunk);
		return w;
	}
};

TEST_F(VoxelMeshGeneratorTests, EmptyChunk)
{
	// arrange
	Voxel_chunk c{ 2, 2 };
	World w{ create_world_with_single_chunk(c) };

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::IsEmpty());
}

TEST_F(VoxelMeshGeneratorTests, SingleBlockChunk)
{
	// arrange
	Voxel_chunk c{ 3, 4 };
	c.set_block(1, 1, 1, Voxel_type::Stone);
	World w{ create_world_with_single_chunk(c) };

	vec3 displacement{ 1,1,1 };
	std::vector<Face> expected_faces{
		Voxel_mesh_generator::top1_face + displacement,
		Voxel_mesh_generator::top2_face + displacement,
		Voxel_mesh_generator::left1_face + displacement,
		Voxel_mesh_generator::left2_face + displacement,
		Voxel_mesh_generator::right1_face + displacement,
		Voxel_mesh_generator::right2_face + displacement,
		Voxel_mesh_generator::bottom1_face + displacement,
		Voxel_mesh_generator::bottom2_face + displacement,
		Voxel_mesh_generator::front1_face + displacement,
		Voxel_mesh_generator::front2_face + displacement,
		Voxel_mesh_generator::back1_face + displacement,
		Voxel_mesh_generator::back2_face + displacement,
	};

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::UnorderedElementsAreArray(expected_faces));
}

TEST_F(VoxelMeshGeneratorTests, FlatChunk)
{
	// arrange
	Voxel_chunk c{ 2, 4 };
	c.set_layer(0, Voxel_type::Stone);
	World w{ create_world_with_single_chunk(c) };

	std::vector<Face> expected_faces{
		Voxel_mesh_generator::top1_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 1),
	};

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::UnorderedElementsAreArray(expected_faces));
}

TEST_F(VoxelMeshGeneratorTests, CornerProtrudingBlockLeftFront)
{
	// arrange
	Voxel_chunk c{ 2, 3 };
	c.set_layer(0, Voxel_type::Stone);
	c.set_block(0, 1, 0, Voxel_type::Stone);
	World w{ create_world_with_single_chunk(c) };

	std::vector<Face> expected_faces{
		Voxel_mesh_generator::top1_face + vec3(0, 1, 0),
		Voxel_mesh_generator::top2_face + vec3(0, 1, 0),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 1),

		Voxel_mesh_generator::back1_face + vec3(0, 1, 0),
		Voxel_mesh_generator::back2_face + vec3(0, 1, 0),
		Voxel_mesh_generator::right1_face + vec3(0, 1, 0),
		Voxel_mesh_generator::right2_face + vec3(0, 1, 0),
	};

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::UnorderedElementsAreArray(expected_faces));
}

TEST_F(VoxelMeshGeneratorTests, CornerProtrudingBlockRightFront)
{
	// arrange
	Voxel_chunk c{ 2, 3 };
	c.set_layer(0, Voxel_type::Stone);
	c.set_block(1, 1, 0, Voxel_type::Stone);
	World w{ create_world_with_single_chunk(c) };

	std::vector<Face> expected_faces{
		Voxel_mesh_generator::top1_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(1, 1, 0),
		Voxel_mesh_generator::top2_face + vec3(1, 1, 0),
		Voxel_mesh_generator::top1_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 1),

		Voxel_mesh_generator::back1_face + vec3(1, 1, 0),
		Voxel_mesh_generator::back2_face + vec3(1, 1, 0),
		Voxel_mesh_generator::left1_face + vec3(1, 1, 0),
		Voxel_mesh_generator::left2_face + vec3(1, 1, 0),
	};

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::UnorderedElementsAreArray(expected_faces));
}

TEST_F(VoxelMeshGeneratorTests, CornerProtrudingBlockLeftBack)
{
	// arrange
	Voxel_chunk c{ 2, 3 };
	c.set_layer(0, Voxel_type::Stone);
	c.set_block(0, 1, 1, Voxel_type::Stone);
	World w{ create_world_with_single_chunk(c) };

	std::vector<Face> expected_faces{
		Voxel_mesh_generator::top1_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(0, 1, 1),
		Voxel_mesh_generator::top2_face + vec3(0, 1, 1),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 1),

		Voxel_mesh_generator::front1_face + vec3(0, 1, 1),
		Voxel_mesh_generator::front2_face + vec3(0, 1, 1),
		Voxel_mesh_generator::right1_face + vec3(0, 1, 1),
		Voxel_mesh_generator::right2_face + vec3(0, 1, 1),
	};

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::UnorderedElementsAreArray(expected_faces));
}

TEST_F(VoxelMeshGeneratorTests, CornerProtrudingBlockRightBack)
{
	// arrange
	Voxel_chunk c{ 2, 3 };
	c.set_layer(0, Voxel_type::Stone);
	c.set_block(1, 1, 1, Voxel_type::Stone);
	World w{ create_world_with_single_chunk(c) };

	std::vector<Face> expected_faces{
		Voxel_mesh_generator::top1_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top2_face + vec3(1, 0, 0),
		Voxel_mesh_generator::top1_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top2_face + vec3(0, 0, 1),
		Voxel_mesh_generator::top1_face + vec3(1, 1, 1),
		Voxel_mesh_generator::top2_face + vec3(1, 1, 1),

		Voxel_mesh_generator::front1_face + vec3(1, 1, 1),
		Voxel_mesh_generator::front2_face + vec3(1, 1, 1),
		Voxel_mesh_generator::left1_face + vec3(1, 1, 1),
		Voxel_mesh_generator::left2_face + vec3(1, 1, 1),
	};

	// act
	auto actual_faces = Voxel_mesh_generator::generate(0, 0, w);

	// assert
	EXPECT_THAT(actual_faces, ::testing::UnorderedElementsAreArray(expected_faces));
}
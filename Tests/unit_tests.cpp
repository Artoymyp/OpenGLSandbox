#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Vertex.h>
#include <Face.h>
#include <World.h>

TEST(VertexTests, Equal) {
	Vertex v0(0, 0, 0, 0, 0);
	Vertex v1(1, 0, 0, 0, 0);
	Vertex v2(0, 1, 0, 0, 0);
	Vertex v3(0, 0, 1, 0, 0);
	Vertex v4(0, 0, 0, 1, 0);
	Vertex v5(0, 0, 0, 0, 1);
	
	EXPECT_TRUE(v0 == v0);
	EXPECT_TRUE(v0 != v1);
	EXPECT_TRUE(v0 != v2);
	EXPECT_TRUE(v0 != v3);
	EXPECT_TRUE(v0 != v4);
	EXPECT_TRUE(v0 != v5);
}	

TEST(FaceTests, Equal) {
	Vertex v0(0, 0, 0, 0, 0);
	Vertex v1(1, 0, 0, 0, 0);
	Face f0(v0, v0, v0);
	Face f1(v1, v0, v0);
	Face f2(v0, v1, v0);
	Face f3(v0, v0, v1);

	EXPECT_TRUE(f0 == f0);
	EXPECT_TRUE(f0 != f1);
	EXPECT_TRUE(f0 != f2);
	EXPECT_TRUE(f0 != f3);
}

TEST(FaceTests, FacePlusVec3) {
	// arrange
	Face f0{
		Vertex{0, 0, 1, 0, 0},
		Vertex{1, 1, 1, 1, 1},
		Vertex{0, 1, 1, 0, 1}
	};

	Face expected_face{
		Vertex{1, 2, 4, 0, 0},
		Vertex{2, 3, 4, 1, 1},
		Vertex{1, 3, 4, 0, 1}
	};

	// act
	auto f1 = f0 + glm::vec3(1, 2, 3);

	// assert
	EXPECT_THAT(f1, expected_face);
}

TEST(VoxelChunk, InitializedByAir)
{
	// arrange
	Voxel_chunk c;

	// assert
	for (int x = 0; x < c.width; x++) {
		for (int y = 0; y < c.width; y++) {
			for (int z = 0; z < c.width; z++) {
				ASSERT_THAT(c.get_block(x, y, z), Voxel_type::Air);
			}
		}
	}
}

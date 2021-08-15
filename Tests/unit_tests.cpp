#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Vertex.h>
#include <Face.h>

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


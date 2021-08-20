#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Physics_engine.h>


struct PhysXTests : public ::testing::Test {

};


TEST_F(PhysXTests, Test)
{
	// arrange
	Physics_engine a;
	a.init();
	// act
	
	std::vector<Face> faces{
		Face(Vertex(0,0,0,0,0), Vertex(0,1,0,0,1), Vertex(1,1,0,1,1)) 
	};
	a.create_terrain(faces);

	// assert
	//EXPECT_THAT(actual_faces, ::testing::IsEmpty());
}

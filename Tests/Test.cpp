#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../LogicLib/logic.h"
#include <fstream>

std::string makeAndFillInputFile()
{
	std::string fileName("test1.obj");
	std::ofstream fileStream(fileName);
	fileStream << "v 0.038060 3.980785 -0.191342" << std::endl;
	return fileName;
}

bool basicMeshTest1()
{
	const auto inputFile = makeAndFillInputFile();
	const auto myMesh = parseObjFile(inputFile.c_str());
	return myMesh.vertices.size() == 1 &&
		myMesh.vertices[0] == QVector3D(std::stof("0.038060"),
			std::stof("3.980785"), std::stof("-0.191342")) &&
		myMesh.triangles.empty();
}

TEST_CASE( "ObjParser Basics", "[ObjParser]" ) {
    REQUIRE(basicMeshTest1());
}

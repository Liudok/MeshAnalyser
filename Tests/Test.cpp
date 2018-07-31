#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../LogicLib/logic.h"
#include <fstream>

std::string makeAndFillInputFile(std::string const& fileName, std::string const& input)
{
	std::ofstream fileStream(fileName);
	fileStream << input << std::endl;
	return fileName;
}

bool correctlyParsesVertex()
{
	const auto inputFile = makeAndFillInputFile("test1.obj",
		"v 0.038060 3.980785 -0.191342");
	const auto myMesh = parseObjFile(inputFile.c_str());
	return myMesh.vertices.size() == 1 &&
		myMesh.vertices[0] == QVector3D(std::stof("0.038060"),
			std::stof("3.980785"), std::stof("-0.191342")) &&
		myMesh.triangles.empty();
}

bool correctlyParsesTriangle()
{
	const auto inputFile = makeAndFillInputFile("test2.obj",
		"v 0.038060 3.980785 -0.191342\n"
		"v 0.038060 3.980785 -0.191342\n"
		"v 0.038060 3.980785 -0.191342\n"
		"f 0//512 1//512 2//512");
	const auto myMesh = parseObjFile(inputFile.c_str());
	return myMesh.vertices.size() == 3 &&
		myMesh.vertices[0] == QVector3D(std::stof("0.038060"),
			std::stof("3.980785"), std::stof("-0.191342"));
		myMesh.vertices[2] == myMesh.vertices[1] &&
		myMesh.vertices[1] == myMesh.vertices[0];
		myMesh.triangles.size() == 1 &&
		myMesh.triangles[0].v1 == 0 &&
		myMesh.triangles[1].v1 == 1 &&
		myMesh.triangles[2].v1 == 2;
}

bool correctlyThrowsExceptionWhenTriangleRequiresNonExistentVertex()
{
	const auto inputFile = makeAndFillInputFile("test3.obj",
		"f 0//512 1//512 2//512");
	auto exceptionThrown = false;
	try {
		const auto myMesh = parseObjFile(inputFile.c_str());
	}
	catch (std::runtime_error& e) {
		exceptionThrown = true;
	}
	return exceptionThrown;
}

TEST_CASE( "ObjParser Basics", "[ObjParser]" ) {
    REQUIRE(correctlyParsesVertex());
	REQUIRE(correctlyParsesTriangle());
	REQUIRE(correctlyThrowsExceptionWhenTriangleRequiresNonExistentVertex());
}

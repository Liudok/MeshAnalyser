#include "logic.h"
#include <fstream>
#include <string>
#include <regex>

namespace
{
	QVector3D parseVertex(std::string const& line) noexcept
	{
		return QVector3D(std::stof(&line[line.find(' ') + 1]),
			std::stof(&line[line.find(' ', 2) + 1]),
			std::stof(&line[line.find_last_of(' ') + 1]));
	}
	Triangle parseTriangle(std::string const& line, size_t nbVertices)
	{
		Triangle triangle;
		triangle.v1 = std::stoll(&line[line.find(' ') + 1]);
		triangle.v2 = std::stoll(&line[line.find(' ', 2) + 1]);
		triangle.v3 = std::stoll(&line[line.find_last_of(' ') + 1]);
		if (triangle.v1 > nbVertices || triangle.v2 > nbVertices ||
			triangle.v3 > nbVertices)
			throw std::runtime_error("Invalid index of vertex");
		return triangle;
	}
}

Mesh parseObjFile(const char* fileName)
{
	std::regex verticesPattern("^v([ ][-]?[0-9]+[\\.][0-9]+){3}$");
	std::regex trianglesPattern("^f([ ][0-9]+//[0-9]+){3}$");
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("Failed to open the file");
	Mesh result;
	for (std::string line; std::getline(file, line);) {
		if (std::regex_match(line, verticesPattern))
			result.vertices.push_back(parseVertex(line));
		else if (std::regex_match(line, trianglesPattern))
			result.triangles.push_back(parseTriangle(line, result.vertices.size()));
	}
	return result;
}

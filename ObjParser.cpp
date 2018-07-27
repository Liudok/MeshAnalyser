#include "Mesh.h"
#include <fstream>
#include <string>
#include <regex>
#include <iostream>

namespace
{
	QVector3D parseVertex(std::string const& line)
	{
		return QVector3D(std::stof(&line[line.find(' ') + 1]),
			std::stof(&line[line.find(' ', 2) + 1]),
				std::stof(&line[line.find_last_of(' ') + 1]));
	}
}


Mesh parseObjFile(const char* fileName)
{
	std::regex verticesPattern("^v([ ][-]?[0-9]+[\\.][0-9]+){3}");
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("Failed to open the file");
	Mesh result;
	for (std::string line; std::getline(file, line);) {
		if (std::regex_match(line, verticesPattern))
			result.vertices.push_back(parseVertex(line));
	}
	return result;
}

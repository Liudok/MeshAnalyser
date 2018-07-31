#include "logic.h"
#include <fstream>
#include <string>
#include <regex>
#include <vector>

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

namespace
{
	bool nearlyEqual(float a, float b)
	{
		const auto epsilon = 10e-6;
		return std::abs(a - b) < epsilon;
	}

	bool pointsIntersect(QVector3D const& p1, QVector3D const& p2)
	{
		return nearlyEqual(p1.x(), p2.x()) &&
			nearlyEqual(p1.y(), p2.y());
	}

	int findClosestToViewerPointIndex(QVector<QVector3D> const& vertices,
		std::vector<int> const& intersectingPointsIndices)
	{
		const int notFound = -1;
		if (intersectingPointsIndices.empty()) return notFound;
		float minZ = std::numeric_limits<float>::max();
		int bestPointIndex = 0;
		for (auto index : intersectingPointsIndices) {
			if (vertices[index].z() < minZ) {
				minZ = vertices[index].z();
				bestPointIndex = index;
			}
		}
		return bestPointIndex;
	}
}

int findIndexOfVertexPointedAt(QVector<QVector3D> const& vertices,
	QVector3D const& click)
{
	if (vertices.size() > std::numeric_limits<int>::max())
		throw std::runtime_error("The vector contains to many points");
	std::vector<int> intersectingPointsIndices;
	for (int i = 0; i < vertices.size(); ++i)
		if (pointsIntersect(vertices[i], click))
			intersectingPointsIndices.push_back(i);
	return findClosestToViewerPointIndex(vertices, intersectingPointsIndices);
}

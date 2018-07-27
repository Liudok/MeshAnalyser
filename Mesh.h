#pragma once

#include <QVector3D>
#include <vector>

struct Triangle
{
	size_t v1 = 0;
	size_t v2 = 0;
	size_t v3 = 0;
};

struct Mesh
{
	std::vector<QVector3D> vertices;
	std::vector<Triangle> triangles;
};

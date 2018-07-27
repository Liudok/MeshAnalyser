#pragma once

#include <QVector3D>
#include <vector>

struct Triangle
{
	size_t v1;
	size_t v2;
	size_t v3;
};

struct Mesh
{
	std::vector<QVector3D> vertices;
	std::vector<Triangle> triangles;
};

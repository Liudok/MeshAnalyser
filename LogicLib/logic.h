#pragma once

#include "../Mesh/Mesh.h"

Mesh parseObjFile(const char* fileName);

int findIndexOfVertexPointedAt(QVector<QVector3D> const& vertices,
	QVector3D const& click);

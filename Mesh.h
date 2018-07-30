#pragma once

#include <QVector3D>
#include <QVector>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QKeyEvent>

struct Triangle
{
	GLuint v1 = 0;
	GLuint v2 = 0;
	GLuint v3 = 0;
};

struct Mesh
{
	QVector<QVector3D> vertices;
	QVector<Triangle> triangles;
};

#pragma once
#include <QVector3D>

struct Point
{
	QVector3D p; //point x, y, z
	QVector3D c; //color red, green, blue

	Point() {}

	Point(float xp, float yp, float zp)
	{
		p = QVector3D(xp, yp, zp);
		c = QVector3D(0, 0, 0);
	}
	Point(QVector3D pos, unsigned char r, unsigned char g, unsigned char b)
	{
		p = pos;
		c = QVector3D(static_cast<float>(r) / 255.f,
			static_cast<float>(g) / 255.f,
			static_cast<float>(b) / 255.f);
	}
};

struct Triangle
{
	Point vertices[3];

	Triangle()
	{
	}

	Triangle(Point p1, Point p2, Point p3)
	{
		vertices[0] = p1;
		vertices[1] = p2;
		vertices[2] = p3;
	}

};
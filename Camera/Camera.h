#pragma once

#include <qvector3d.h>
#include <qopengl.h>
#include <qmatrix4x4.h>

class Camera
{
public:
	Camera(const QVector3D &position, const QVector3D &viewCenter = QVector3D(0, 0, 0), const QVector3D &upVector = QVector3D(0, 1, 0));

	void shift(const QVector3D &translate);
	void rotate();
	void zoom(double delta);

	QMatrix4x4 getViewMatrix() const;
	QVector3D getPosition() const;

	void setPosition(const QVector3D &position);

private:
	QVector3D m_position;
	QVector3D m_viewCenter;
	QVector3D m_upVector;
	QMatrix4x4 m_viewMatrix;
};

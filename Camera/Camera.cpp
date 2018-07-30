#include "Camera.h"

Camera::Camera(const QVector3D &position, const QVector3D &viewCenter, const QVector3D &upVector)
	:m_position(position), m_viewCenter(viewCenter), m_upVector(upVector)
{
	m_viewMatrix.lookAt(position, viewCenter, upVector);
}

QMatrix4x4 Camera::getViewMatrix() const
{
	return m_viewMatrix;
}

QVector3D Camera::getPosition() const
{
	return m_position;
}

void Camera::setPosition(const QVector3D &position)
{
	m_position = position;
}

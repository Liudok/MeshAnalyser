#include "Camera.h"

Camera::Camera(const QVector3D &position, const QVector3D &viewCenter, const QVector3D &upVector)
	:m_position(position), m_viewCenter(viewCenter), m_upVector(upVector)
{
	lookAt();
}

void Camera::lookAt()
{
	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(m_position, m_viewCenter, m_upVector);
}

QMatrix4x4 Camera::getViewMatrix() const
{
	return m_viewMatrix;
}

void Camera::setViewMatrix(const QMatrix4x4 &view)
{
	m_viewMatrix = view;
}

QVector3D Camera::getPosition() const
{
	return m_position;
}

void Camera::setPosition(const QVector3D &position)
{
	m_position = position;
}

QVector3D Camera::getViewCenter() const
{
	return m_viewCenter;
}

void Camera::setViewCenter(const QVector3D &viewCenter)
{
	m_viewCenter = viewCenter;
}
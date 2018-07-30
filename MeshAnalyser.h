#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MeshAnalyser.h"
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QKeyEvent>


class MeshAnalyser : public QMainWindow
{
	Q_OBJECT

public:
	MeshAnalyser(QWidget *parent = Q_NULLPTR);

private:
	Ui::MeshAnalyserClass ui;
	Ui::Widget* openGLWidget;
};

class Ui::Widget : public QOpenGLWidget
	{
	Q_OBJECT

	public:
		explicit Widget(QWidget *parent = nullptr);

	private:
		QOpenGLTexture *m_texture;
		QOpenGLBuffer m_indexBuffer;
		QMatrix4x4 m_projectionMatrix;
		QOpenGLShaderProgram m_program;
		QOpenGLBuffer m_arrayBuffer;
		QVector2D m_mousePosition;
		QQuaternion m_rotation;

	protected:
		//void initializeGL();
		//void resizeGL(int w, int h);
		//void paintGL();

		//void mousePressEvent(QMouseEvent * event);
		//void mouseMoveEvent(QMouseEvent * event);

		//void initShaders();
		//void initMesh(float width);
	};

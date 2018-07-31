#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MeshAnalyser.h"
#include "Mesh.h"
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QKeyEvent>

struct VertexData
{
	VertexData() {}
	VertexData(QVector3D p, QVector2D t, QVector3D n) :
		position(p),
		texCoord(t),
		normal(n) {}
	QVector3D position;
	QVector2D texCoord;
	QVector3D normal;
};


class Widget;
class MeshAnalyser : public QMainWindow
{
	Q_OBJECT

public:
	MeshAnalyser(QWidget *parent = Q_NULLPTR);
	void setMesh(Mesh input);
private:
	Ui::MeshAnalyserClass ui;
	Widget* openGLWidget;
};

class Widget : public QOpenGLWidget
	{
	Q_OBJECT

	public:
		explicit Widget(QWidget *parent = nullptr);
		Mesh myMesh;
	private:
		QOpenGLTexture *m_texture;
		QOpenGLBuffer m_indexBuffer;
		QMatrix4x4 m_projectionMatrix;
		QOpenGLShaderProgram *m_program;
		QOpenGLBuffer m_arrayBuffer;
		QVector2D m_mousePosition;
		QQuaternion m_rotation;

	protected:
		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();

		void mousePressEvent(QMouseEvent * event);
		void mouseMoveEvent(QMouseEvent * event);

		void initShaders();
		void initMesh(Mesh myMesh);
		void initCube(float width);
	};

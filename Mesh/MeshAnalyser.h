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

/*
program->addShaderFromSourceCode(QGLShader::Vertex,
"attribute highp vec4 vertex;"
"attribute mediump mat4 matrix;"
"void main(void)"
"{"
" gl_Position = matrix * vertex;"
"}");
program->addShaderFromSourceCode(QGLShader::Fragment,
"uniform mediump vec4 color;"
"void main(void)"
"{"
" gl_FragColor = color;"
"}");
program->link();

}
void MyQGLWidget::paintGL()
{
glClear(GL_COLOR_BUFFER_BIT );
program->bind();
QVector3D triangleVertices[] = {
QVector3D(0, 0.0f, 1.0f),
QVector3D(0, 1.0f, 1.0f),
QVector3D(1.0f, 0, 1.0f)
};

int vertexLocation = program->attributeLocation("vertex");
int colorLocation = program->attributeLocation("color");
int matrixLocation = program->attributeLocation("matrix");

QMatrix4x4 pmvMatrix;

program->enableAttributeArray(vertexLocation);
program->setAttributeArray(vertexLocation, triangleVertices);
program->setUniformValue(matrixLocation, pmvMatrix);
program->setUniformValue(colorLocation, QColor(1, 1, 1));

glDrawArrays(GL_TRIANGLES, 0, 3);

program->disableAttributeArray(vertexLocation);
program->release();
}

*/


class Widget;
class MeshAnalyser : public QMainWindow
{
	Q_OBJECT

public:
	MeshAnalyser(QWidget *parent = Q_NULLPTR);

private:
	Ui::MeshAnalyserClass ui;
	Widget* openGLWidget;
};

class Widget : public QOpenGLWidget
	{
	Q_OBJECT

	public:
		explicit Widget(QWidget *parent = nullptr);

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

		bool eventFilter(QObject *obj, QEvent *ev);

		void mousePressEvent(QMouseEvent * event) override;
		void mouseMoveEvent(QMouseEvent * event) override;

		void initShaders();
		//void initMesh(float width);
		void initCube(float width);
	};

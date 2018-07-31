#include "Camera.h"
#include "openglwindow.h"


#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include <Qt3DCore/qtransform.h>
#include<math.h>
#include <qevent.h>

//! [1]
class TriangleWindow : public OpenGLWindow
{
public:
	TriangleWindow();

	void initialize() override;
	void render() override;

	void wheelEvent(QWheelEvent *we) override;
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;

private:
	GLuint m_posAttr;
	GLuint m_colAttr;
	GLuint m_model;
	GLuint m_view;
	GLuint m_projection;
	GLuint m_mvp;

	QMatrix4x4 m_matrixModel;
	QMatrix4x4 m_matrixView;
	QMatrix4x4 m_matrixProjection;
	QMatrix4x4 m_matrixMVP;

	QMatrix4x4 m_cameraStart;
	QPoint m_mouseStart;

	QOpenGLShaderProgram *m_program;
	int m_frame;

	int m_mouseButton;

	bool m_mousePressed;

	Camera *m_camera;
};

TriangleWindow::TriangleWindow()
	: m_program(0)
	, m_frame(0)
{
}
//! [1]

//! [2]
int main(int argc, char **argv)
{
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(16);

	TriangleWindow window;
	window.setFormat(format);
	window.resize(640, 480);
	window.show();

	window.setAnimating(true);

	return app.exec();
}
//! [2]


//! [3]
static const char *vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 model;\n"
"uniform highp mat4 view;\n"
"uniform highp mat4 proj;\n"
"uniform highp mat4 MVP;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = MVP * posAttr;\n"
"}\n";

static const char *fragmentShaderSource =
"varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";
//! [3]

//! [4]
void TriangleWindow::initialize()
{
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	m_program->link();
	m_posAttr = m_program->attributeLocation("posAttr");
	m_colAttr = m_program->attributeLocation("colAttr");
	m_model = m_program->uniformLocation("model");
	m_view = m_program->uniformLocation("view");
	m_projection = m_program->uniformLocation("proj");
	m_mvp = m_program->uniformLocation("MVP");
	m_matrixProjection.setToIdentity();
	m_matrixProjection.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	m_matrixModel.setToIdentity();
	m_matrixModel.scale(0.1);
	m_camera = new Camera(QVector3D(0, 0, 1), QVector3D(0, 0, 0), QVector3D(0, -1, 0));
}
//! [4]

//! [5]
void TriangleWindow::render()
{
	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	glClear(GL_COLOR_BUFFER_BIT);

	m_program->bind();

	m_matrixView = m_camera->getViewMatrix();

	m_matrixMVP = m_matrixProjection*m_matrixView*m_matrixModel;
	m_program->setUniformValue(m_mvp, m_matrixMVP);

	GLfloat vertices[] = {
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	m_program->release();

	++m_frame;

}
//! [5]

void TriangleWindow::wheelEvent(QWheelEvent *we)
{
	double delta = we->delta() / 100.0;
	if (delta < 0) delta = -1 / delta;
	m_matrixModel.scale(delta);
}


void TriangleWindow::mousePressEvent(QMouseEvent *ev)
{
	m_mousePressed = true;
	m_mouseStart = ev->pos();
	m_cameraStart = m_camera->getViewMatrix();
	if(ev->button()==Qt::MouseButton::LeftButton)
	m_mouseButton = 1;
	if (ev->button() == Qt::MouseButton::RightButton)
	m_mouseButton = 2;
}

void TriangleWindow::mouseMoveEvent(QMouseEvent *ev)
{
	if (m_mousePressed && m_mouseButton == 2)
	{
		QPoint delta = ev->pos() - m_mouseStart;

		QMatrix4x4 translate;
		translate.setToIdentity();
		translate.translate(QVector3D(delta.x() / 800.0, -delta.y() / 600.0, 0));

		QMatrix4x4 newView = translate*m_cameraStart;

		m_camera->setViewMatrix(newView);
	}
	if (m_mousePressed && m_mouseButton == 1)
	{
		QPoint delta = ev->pos() - m_mouseStart;
		
		float radius = 10.0;
		QVector3D v;
		v.setZ (m_camera->getPosition().z());
		v.setX( std::sin(delta.x()*radius/800.));
		v.setY( std::cos(delta.y()*radius/600.));
		m_camera->setPosition(v);
		m_camera->lookAt();
	}
}

void TriangleWindow::mouseReleaseEvent(QMouseEvent *ev)
{
	m_mousePressed = false;
	m_mouseButton = 0;
}
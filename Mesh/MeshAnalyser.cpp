#include "MeshAnalyser.h"
#include <QGLShader>
#include <qopenglfunctions.h>

MeshAnalyser::MeshAnalyser(QWidget *parent)
	: QMainWindow(parent),
	openGLWidget(new Widget(this))
{
	openGLWidget->setMinimumSize(400, 400);
	ui.setupUi(this);
}

void MeshAnalyser::setMesh(Mesh input)
{
	openGLWidget->myMesh = input;
}

Widget::Widget(QWidget *parent) :
	QOpenGLWidget(parent),
	m_texture(nullptr),
	m_indexBuffer(QOpenGLBuffer::IndexBuffer) {}


void Widget::initializeGL()
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glClearColor(0.2f, 0.4f, 0.0f, 1.0f);

	f->glEnable(GL_DEPTH_TEST);
	f->glEnable(GL_CULL_FACE);

	initShaders();
	initMesh(myMesh);
//	initCube(0.30f);

}

void Widget::resizeGL(int w, int h)
{
	float aspect = w / static_cast<float>(h);
	m_projectionMatrix.setToIdentity();
	m_projectionMatrix.perspective(45, aspect, 0.1, 10);
}

void Widget::paintGL()
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	QMatrix4x4 modelViewMatrix;
	modelViewMatrix.setToIdentity();
	modelViewMatrix.translate(0.0, 0.0, -1.0);
	modelViewMatrix.rotate(m_rotation);
	//	m_texture->bind(0);

	m_program->bind();
	m_program->setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * modelViewMatrix);
	m_program->setUniformValue("qt_Texture0", 0);

	m_arrayBuffer.bind();

	int offset = 0;

	int vertLoc = m_program->attributeLocation("qt_Vertex");
	m_program->enableAttributeArray(vertLoc);
	m_program->setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(QVector3D));

	m_program->release();


	////m_program->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

	/*offset += sizeof(QVector3D);

	int texLoc = m_program->attributeLocation("qt_MultiTexCoord0");
	m_program->enableAttributeArray(texLoc);
	m_program->setAttributeBuffer(texLoc, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

*/
	/*	offset += sizeof(QVector3D);

		int texLoc = m_program.attributeLocation("qt_MultiTexCoord0");
		m_program.enableAttributeArray(texLoc);
		m_program.setAttributeBuffer(texLoc, GL_FLOAT, sizeof(QVector3D), 2, sizeof(QVector3D));
		*/
	m_indexBuffer.bind();

	f->glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Widget::mousePressEvent(QMouseEvent *event)
	{
	if(event->buttons() == Qt::LeftButton)
		m_mousePosition = QVector2D(event->localPos());
	event->accept();
	}

void Widget::mouseMoveEvent(QMouseEvent *event)
	{
	if(event->buttons() != Qt::LeftButton)
		return;
	QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
	m_mousePosition = QVector2D(event->localPos());

	float angle = diff.length() / 2.0;

	QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

	m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;

	update();

	}

void Widget::initShaders()
{
	m_program = new QOpenGLShaderProgram(this);
	const char *vshader = "attribute highp vec4 qt_Vertex; attribute highp vec2 qt_MultiTexCoord0; uniform highp mat4 qt_ModelViewProjectionMatrix;\
	varying highp vec2 qt_TexCoord0;void main(void)\
	{\
		gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;\
		qt_TexCoord0 = qt_MultiTexCoord0;\
	}";
	if (!m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vshader))
	{
		QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
		f->glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}
	const char *fshader = "uniform sampler2D qt_Texture0;\
varying highp vec2 qt_TexCoord0;\
void main(void){\
gl_FragColor = vec4(1.0, 0.2, 0.5, 1.0);\
\
}";
	if (!m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fshader))
	{
		QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
		f->glClearColor(0.9f, 0.0f, 0.0f, 1.0f);
	}

	if (!m_program->link())
		 close();


	//	if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
	//		close();
	//	if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
	//		close();
	//	if(!m_program.link())
	//		close();
}

void Widget::initMesh(Mesh myMesh)
{
	//QVector<QVector3D> vertexes;
	//for (int i = 0; i < myMesh.vertices.size(); i++)
	//{
	//	vertexes.append(QVector3D(myMesh.vertices[i].x(), myMesh.vertices[i].y(), myMesh.vertices[i].z()));
	//}


	QVector<GLuint>indexes;
	for (int i = 0; i < myMesh.triangles.size(); i++)
	{
		indexes.append(myMesh.triangles[i].v1);
		indexes.append(myMesh.triangles[i].v2);
		indexes.append(myMesh.triangles[i].v3);
	}
	m_arrayBuffer.create();
	m_arrayBuffer.bind();
	m_arrayBuffer.allocate(myMesh.vertices.constData(), myMesh.vertices.size() * sizeof(QVector3D));
	m_arrayBuffer.release();

	m_indexBuffer.create();
	m_indexBuffer.bind();
	m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
	m_indexBuffer.release();


}



/*
void Widget::initCube(float width)
{
	float width_div_2 = width / 2.0f;
	QVector<VertexData> vertexes;
	vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

	vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

	vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

	vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));


	vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));


	vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
	vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
	vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

	QVector<GLuint>indexes;
	for (int i = 0; i < 24; i += 4)
	{
		indexes.append(i + 0);
		indexes.append(i + 1);
		indexes.append(i + 2);
		indexes.append(i + 2);
		indexes.append(i + 1);
		indexes.append(i + 3);
	}
	m_arrayBuffer.create();
	m_arrayBuffer.bind();
	m_arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
	m_arrayBuffer.release();

	m_indexBuffer.create();
	m_indexBuffer.bind();
	m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
	m_indexBuffer.release();

	m_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
	m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
	m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
	m_texture->setWrapMode(QOpenGLTexture::Repeat);

}

*/
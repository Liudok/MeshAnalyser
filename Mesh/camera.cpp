#include "camera.h"

CameraWindow::CameraWindow()
{
	m_view = new Qt3DExtras::Qt3DWindow();
	m_view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

	m_view->installEventFilter(this);

	QWidget *container = QWidget::createWindowContainer(m_view);
	QSize screenSize = m_view->screen()->size();
	container->setMinimumSize(QSize(200, 100));
	container->setMaximumSize(screenSize);

	m_widget = new QWidget;
	QHBoxLayout *hLayout = new QHBoxLayout(m_widget);
	QVBoxLayout *vLayout = new QVBoxLayout();
	vLayout->setAlignment(Qt::AlignTop);
	hLayout->addWidget(container, 1);
	hLayout->addLayout(vLayout);

	m_rootEntity = new Qt3DCore::QEntity();

	m_widget->setWindowTitle(QStringLiteral("Basic shapes"));

	Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
	m_view->registerAspect(input);

	m_view->setRootEntity(m_rootEntity);

	m_startPoint = QPoint(-1, -1);
}

CameraWindow::~CameraWindow()
{
	delete m_camera;
}

void CameraWindow::initCamera(const QVector3D &position, const QVector3D &viewCenter, const QVector3D &upVector)
{
	m_camera = m_view->camera();
	int width = m_view->width();
	int height = m_view->height();
	//m_camera->lens()->setOrthographicProjection(-width / 2, width / 2, height / 2, -height / 2, 0, -100);
	m_camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_camera->setPosition(position);
	m_camera->setViewCenter(viewCenter);
	m_camera->setUpVector(upVector);

	Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(m_rootEntity);
	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
	light->setColor("white");
	light->setIntensity(1);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(m_camera->position());
	lightEntity->addComponent(lightTransform);

	/*Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(m_rootEntity);
	camController->setCamera(m_camera);*/
}

void CameraWindow::show()
{
	m_widget->show();
	m_widget->resize(800, 600);
}

void CameraWindow::addTorus()
{
	// Torus shape data
	//! [0]
	Qt3DExtras::QTorusMesh *torus = new Qt3DExtras::QTorusMesh();
	torus->setRadius(1.0f);
	torus->setMinorRadius(0.4f);
	torus->setRings(100);
	torus->setSlices(20);
	//! [0]

	// TorusMesh Transform
	//! [1]
	Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform();
	torusTransform->setScale(2.0f);
	torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
	torusTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
	//! [1]

	//! [2]
	Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial();
	torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
	//! [2]

	// Torus
	//! [3]
	Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(m_rootEntity);
	torusEntity->addComponent(torus);
	torusEntity->addComponent(torusMaterial);
	torusEntity->addComponent(torusTransform);
	//! [3]

	torusEntity->setEnabled(true);
}

bool CameraWindow::eventFilter(QObject *obj, QEvent *ev)
{
	if (ev->type() == QEvent::Wheel)
	{
		wheelEvent(dynamic_cast<QWheelEvent*>(ev));
		return true;
	}
	else if (ev->type() == QEvent::MouseButtonPress)
	{
		mousePressEvent(dynamic_cast<QMouseEvent*>(ev));
		return true;
	}
	else if (ev->type() == QEvent::MouseMove)
	{
		mouseMoveEvent(dynamic_cast<QMouseEvent*>(ev));
		return true;
	}
	else if (ev->type() == QEvent::MouseButtonRelease)
	{
		mouseReleaseEvent(dynamic_cast<QMouseEvent*>(ev));
		return true;
	}

	return QObject::eventFilter(obj, ev);
}

void CameraWindow::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::MouseButton::RightButton)
	{
		m_startPoint = ev->pos();
		m_cameraMatrix = m_view->camera()->transform()->matrix();
	}
}

void CameraWindow::mouseMoveEvent(QMouseEvent *ev)
{
	if (m_startPoint.x() > -1)
	{
		float dx = ev->pos().x() - m_startPoint.x();
		float dy = ev->pos().y() - m_startPoint.y();
		QMatrix4x4 translation;
		translation.setToIdentity();
		translation.translate(QVector3D(dx, dy, 0));
		QMatrix4x4 matrix = translation * m_cameraMatrix;
		m_camera->transform()->setMatrix(matrix);
	}
}

void CameraWindow::mouseReleaseEvent(QMouseEvent *ev)
{
	m_startPoint = QPoint(-1, -1);
}

void CameraWindow::wheelEvent(QWheelEvent *we)
{
	Qt3DCore::QTransform* transform = m_view->camera()->transform();

	float scale = transform->scale();
	QPoint delta = we->angleDelta();
	float zoom_distance = scale * static_cast<float>(delta.y()) / 500.f;
	scale += zoom_distance;
	scale = std::min(10.0000f, scale);
	scale = std::max(0.001f, scale);
	transform->setScale(scale);
}
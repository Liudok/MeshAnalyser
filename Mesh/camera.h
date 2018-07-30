#ifndef CAMERA_H
#define CAMERA_H

#include <Qt3DRender/qcamera.h>
#include <qvector.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <qscreen.h>
#include <qinputaspect.h>
#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DExtras/qphongmaterial.h>
#include <qevent.h>
#include <qmouseevent.h>

class CameraWindow : public Qt3DExtras::Qt3DWindow
{
	Q_OBJECT
public:
	CameraWindow();
	~CameraWindow();

	void initCamera(const QVector3D &position, const QVector3D &viewCenter = QVector3D(0, 0, 0), const QVector3D &upVector = QVector3D(0, 1, 0));
	void show();
	void addTorus();

	bool eventFilter(QObject *obj, QEvent *ev);

	void mousePressEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void wheelEvent(QWheelEvent *we) override;

private:
	Qt3DRender::QCamera *m_camera;
	QVector3D m_position;
	QVector3D m_viewCenter;
	QVector3D m_upVector;
	Qt3DExtras::Qt3DWindow *m_view;
	Qt3DCore::QEntity *m_rootEntity;
	QWidget *m_widget;
	QPoint m_startPoint;
	QMatrix4x4 m_cameraMatrix;

};

#endif // CAMERA_H

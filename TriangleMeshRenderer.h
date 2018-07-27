#pragma once
#include "Triangle.h"
//#include <QMaterial>

#include <Qt3DRender/qgeometryrenderer.h>

#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>



class TriangleMeshRenderer : public Qt3DRender::QGeometryRenderer
{
	Q_OBJECT
public:
	explicit TriangleMeshRenderer(const std::vector<Triangle>& meshVector, Qt3DCore::QNode *parent = 0);
	~TriangleMeshRenderer();
};


class TriangleMeshGeometry : public Qt3DRender::QGeometry
{
	Q_OBJECT
public:
	TriangleMeshGeometry(const std::vector<Triangle>& meshVector, TriangleMeshRenderer *parent);
};
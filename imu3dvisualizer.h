#ifndef IMU3DVISUALIZER_H
#define IMU3DVISUALIZER_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QRenderAspect>

class IMU3DVisualizer : public Qt3DExtras::Qt3DWindow {
    Q_OBJECT

public:
    IMU3DVisualizer();
    void updateOrientation(float qx, float qy, float qz, float qw);

private:
    Qt3DCore::QEntity *rootEntity;
    Qt3DCore::QTransform *cubeTransform;
};

#endif // IMU3DVISUALIZER_H

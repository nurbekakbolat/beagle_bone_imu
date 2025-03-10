#include "imu3dvisualizer.h"
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QForwardRenderer>
#include <QQuaternion>

IMU3DVisualizer::IMU3DVisualizer() {
    // Create Root Entity
    rootEntity = new Qt3DCore::QEntity();

    // Create a Cube Mesh
    auto *cubeMesh = new Qt3DExtras::QCuboidMesh();

    // Create a Material (Phong shading)
    auto *cubeMaterial = new Qt3DExtras::QPhongMaterial();

    // Create a Transform
    cubeTransform = new Qt3DCore::QTransform();

    // Create the Cube Entity
    auto *cubeEntity = new Qt3DCore::QEntity(rootEntity);
    cubeEntity->addComponent(cubeMesh);
    cubeEntity->addComponent(cubeMaterial);
    cubeEntity->addComponent(cubeTransform);

    // Setup Camera
    auto *camera = this->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 10));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Add Camera Controller
    auto *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(camera);

    // Set Scene Root
    this->setRootEntity(rootEntity);
}

void IMU3DVisualizer::updateOrientation(float qx, float qy, float qz, float qw) {
  // Normalize the quaternion to avoid rotation glitches
  QQuaternion quaternion(qw, qx, qy, qz);
  quaternion.normalize();

  // Apply rotation to the cube
  cubeTransform->setRotation(quaternion);

}


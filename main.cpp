#include <QApplication>
#include "imuclient.h"
#include "imu3dvisualizer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    IMU3DVisualizer visualizer;
    IMUClient client;

    QObject::connect(&client, &IMUClient::imuOrientationReceived, 
                     &visualizer, &IMU3DVisualizer::updateOrientation);

    visualizer.show();
    return app.exec();
}

#include "imuclient.h"
#include <QDebug>

IMUClient::IMUClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &IMUClient::readData);
    connectToServer();
}

void IMUClient::connectToServer() {
  socket->connectToHost("192.168.0.149", 5000);

  if (!socket->waitForConnected(3000)) {
      std::cerr << "Connection Failed!" << std::endl;
  } else {
      std::cout << "Connected to IMU Server!" << std::endl;
  }
}


void IMUClient::readData() {
    QByteArray data = socket->readAll();
    std::string imuString = data.toStdString();

    float qx, qy, qz, qw;
    int parsed = sscanf(imuString.c_str(), "Quat: X=%f, Y=%f, Z=%f, W=%f", &qx, &qy, &qz, &qw);
    
    qDebug() << "Received IMU Data:" << data;
    emit imuDataReceived(data);
    if (parsed == 4) {
        emit imuOrientationReceived(qx, qy, qz, qw);
        std::cout << "Received Quaternion: " << qx << ", " << qy << ", " << qz << ", " << qw << std::endl;
    } else {
        std::cerr << "⚠️ Failed to parse quaternion data: " << imuString << std::endl;
    }
}


#ifndef IMUCLIENT_H
#define IMUCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <iostream>

class IMUClient : public QObject {
    Q_OBJECT  // Ensure Qt MOC processes this class

public:
    explicit IMUClient(QObject *parent = nullptr);
    void connectToServer();

private slots:
    void readData();

signals:
    void imuOrientationReceived(float qx, float qy, float qz, float qw);
    void imuDataReceived(QByteArray data);
private:
    QTcpSocket *socket;
};

#endif // IMUCLIENT_H

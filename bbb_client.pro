TEMPLATE = app
CONFIG += c++11
QT += core network widgets 3dcore 3drender 3dinput 3dlogic 3dextras

SOURCES += main.cpp imuclient.cpp imu3dvisualizer.cpp
HEADERS += imuclient.h imu3dvisualizer.h

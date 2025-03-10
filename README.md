# Client-Side Application for BeagleBone IMU Visualization

This repository contains a client-side application developed to visualize real-time orientation data from an Inertial Measurement Unit (IMU) connected to a BeagleBone Black. The application is built using Qt6 and Qt3D, providing a 3D representation of the IMU's orientation.

## Features

- **Real-Time Visualization**: Displays a 3D cube that mimics the orientation of the IMU in real-time.
- **Quaternion-Based Rotation**: Utilizes quaternion data for smooth and accurate rotation without gimbal lock.
- **Multi-Color Faces**: Each face of the cube is rendered in a distinct color for clear orientation reference.

## Prerequisites

Ensure that the following dependencies are installed on your system:

- **Qt6 Framework**: Including Qt3D modules. Installation instructions can be found on the [Qt website](https://www.qt.io/download).
- **C++ Compiler**: Compatible with C++17 or later.
- **CMake**: Version 3.10 or higher.

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/nurbekakbolat/beagle_bone_imu.git
   cd beagle_bone_imu/client
2. **Configure the Project with QMake:**
    ```qmake && make

  This compiles the source code and produces the executable.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <math.h>
#include "MadgwickAHRS.h"

#define I2C_BUS "/dev/i2c-2"
#define IMU_ADDR 0x6B

void writeRegister(int fd, unsigned char reg, unsigned char value) {
    unsigned char buffer[2] = {reg, value};
    if (write(fd, buffer, 2) != 2) {
        perror("Failed to write to I2C register");
        exit(1);
    }
}

short read16BitRegister(int fd, unsigned char regL, unsigned char regH) {
    unsigned char buffer[1] = {regL};
    if (write(fd, buffer, 1) != 1) {
        perror("Failed to set read register");
        exit(1);
    }
    unsigned char data[2];
    if (read(fd, data, 2) != 2) {
        perror("Failed to read register");
        exit(1);
    }
    return (data[1] << 8) | data[0];
}

int main() {
    int fd = open(I2C_BUS, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return 1;
    }
    if (ioctl(fd, I2C_SLAVE, IMU_ADDR) < 0) {
        perror("Failed to set I2C address");
        return 1;
    }

    writeRegister(fd, 0x10, 0x40); 
    writeRegister(fd, 0x11, 0x40);

    float sampleFreq = 50.0f;


    while (1) {
        short ax = read16BitRegister(fd, 0x28, 0x29);
        short ay = read16BitRegister(fd, 0x2A, 0x2B);
        short az = read16BitRegister(fd, 0x2C, 0x2D);

        short gx = read16BitRegister(fd, 0x22, 0x23);
        short gy = read16BitRegister(fd, 0x24, 0x25);
        short gz = read16BitRegister(fd, 0x26, 0x27);

        float ax_g = ax * (2.0 / 32768.0);
        float ay_g = ay * (2.0 / 32768.0);
        float az_g = az * (2.0 / 32768.0);

        float gx_dps = gx * (245.0 / 32768.0);
        float gy_dps = gy * (245.0 / 32768.0);
        float gz_dps = gz * (245.0 / 32768.0);

        gx_dps *= (M_PI / 180.0f);
        gy_dps *= (M_PI / 180.0f);
        gz_dps *= (M_PI / 180.0f);

        MadgwickAHRSupdateIMU(gx_dps, gy_dps, gz_dps, ax_g, ay_g, az_g);

        // Get quaternion output
        float q0 = MadgwickAHRSgetQ0();
        float q1 = MadgwickAHRSgetQ1();
        float q2 = MadgwickAHRSgetQ2();
        float q3 = MadgwickAHRSgetQ3();

        printf("Accelerometer (g): X=%.3f, Y=%.3f, Z=%.3f\n", ax_g, ay_g, az_g);
        printf("Gyroscope (dps): X=%.3f, Y=%.3f, Z=%.3f\n", gx_dps, gy_dps, gz_dps);
        printf("Quaternion: q0=%.4f, q1=%.4f, q2=%.4f, q3=%.4f\n", q0, q1, q2, q3);

        usleep(20000);
    }

    close(fd);
    return 0;
}

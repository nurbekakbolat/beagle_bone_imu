#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include "MadgwickAHRS.h"

#define I2C_BUS "/dev/i2c-2"
#define IMU_ADDR 0x6B 
#define PORT 5000
#define GYRO_NOISE_THRESHOLD 0.1
float ax_offset = 0, ay_offset = 0, az_offset = 0;
float gx_offset = 0, gy_offset = 0, gz_offset = 0;

// Function Prototypes
void writeRegister(int fd, unsigned char reg, unsigned char value);
short read16BitRegister(int fd, unsigned char regL, unsigned char regH);
void readIMU(float *ax, float *ay, float *az, float *gx, float *gy, float *gz);

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Open I2C bus
    int fd = open(I2C_BUS, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return 1;
    }
    if (ioctl(fd, I2C_SLAVE, IMU_ADDR) < 0) {
        perror("Failed to set I2C address");
        return 1;
    }

    writeRegister(fd, 0x10, 0x60);
    writeRegister(fd, 0x11, 0x80);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return -1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("Listen failed");
        return -1;
    }
    printf("IMU Server is listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    if (client_fd < 0) {
        perror("Client connection failed");
        return -1;
    }
    printf("Client connected!\n");

    int num_samples = 8000;  // Increase calibration samples
    printf("Calibrating IMU... Stay still for 5 seconds!\n");
    for (int i = 0; i < num_samples; i++) {
        float ax, ay, az, gx, gy, gz;
        readIMU(&ax, &ay, &az, &gx, &gy, &gz);
        
        ax_offset += ax;
        ay_offset += ay;
        az_offset += (az - 1.0);
        gx_offset += gx;
        gy_offset += gy;
        gz_offset += gz;
        usleep(1000);
    }

    ax_offset /= num_samples;
    ay_offset /= num_samples;
    az_offset /= num_samples;
    gx_offset /= num_samples;
    gy_offset /= num_samples;
    gz_offset /= num_samples;

    printf("Calibration Done!\n");

    while (1) {
        float ax, ay, az, gx, gy, gz;
        readIMU(&ax, &ay, &az, &gx, &gy, &gz);

        gx *= (M_PI / 180.0f);
        gy *= (M_PI / 180.0f);
        gz *= (M_PI / 180.0f);
        printf("Gyro Raw: X=%.2f, Y=%.2f, Z=%.2f\n", gx, gy, gz);
        if (fabs(gx) < GYRO_NOISE_THRESHOLD && fabs(gy) < GYRO_NOISE_THRESHOLD && fabs(gz) < GYRO_NOISE_THRESHOLD) {
          printf("IMU STATIONARY: Gyro X=%.5f, Y=%.5f, Z=%.5f\n", gx, gy, gz);
      }
        MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az);

        float q0 = MadgwickAHRSgetQ0();
        float q1 = MadgwickAHRSgetQ1();
        float q2 = MadgwickAHRSgetQ2();
        float q3 = MadgwickAHRSgetQ3();
        
        float norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
        q0 /= norm;
        q1 /= norm;
        q2 /= norm;
        q3 /= norm;
        
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Quat: X=%.4f, Y=%.4f, Z=%.4f, W=%.4f\n", q1, q2, q3, q0);
        send(client_fd, buffer, strlen(buffer), 0);

        usleep(1000);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

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

void readIMU(float *ax, float *ay, float *az, float *gx, float *gy, float *gz) {
  int fd = open(I2C_BUS, O_RDWR);
  if (fd < 0) return;
  ioctl(fd, I2C_SLAVE, IMU_ADDR);

  short gx_raw = read16BitRegister(fd, 0x22, 0x23);
  short gy_raw = read16BitRegister(fd, 0x24, 0x25);
  short gz_raw = read16BitRegister(fd, 0x26, 0x27);

  *gx = (gx_raw * (1500.0 / 32768.0)) - gx_offset;
  *gy = (gy_raw * (1500.0 / 32768.0)) - gy_offset;
  *gz = (gz_raw * (1500.0 / 32768.0)) - gz_offset;

  printf("Raw Gyro: X=%d, Y=%d, Z=%d | Corrected: X=%.5f, Y=%.5f, Z=%.5f\n", 
      gx_raw, gy_raw, gz_raw, *gx, *gy, *gz);

  close(fd);
}

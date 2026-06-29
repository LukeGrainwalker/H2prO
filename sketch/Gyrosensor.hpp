#ifndef GYRO_HPP
#define GYRO_HPP

#include "Arduino.h"
#include "Wire.h"

/*
// Wiring for MPU6050:
// Sensor | Arduino UNO
//  VCC   ->  3.3V
//  GND   ->  GND
//  SCL   ->  A5
//  SDA   ->  A4
//  AD0   ->  GND
*/

#define GYRO_DEFAULT_ADDR 0x68  // Default I2C address of MPU6050
#define GYRO_DEFAULT_ACC_RANGE 2 // +-2g
#define GYRO__DEFAULT_RANGE 250 // +- 250°/s
#define GYRO_REG_ACC_START 0x3B // start register for acceleration data
#define GYRO_REG_ACC_SIZE 6
#define GYRO_REG_GYRO_START 0x43 // start register for gyroscope data
#define GYRO_REG_GYRO_SIZE 6
#define GYRO_REG_TEMP_START 0x41 // start register for temperature data
#define GYRO_REG_TEMP_SIZE 2
#define GYRO_1G 16384

struct Acceleration {
    int16_t x, y, z;
};

struct Gyroscope {
    int16_t x, y, z;
};

struct RawSample {
  float temp;
  struct Acceleration acc;
  struct Gyroscope gyro;
};

class Gyro {
public:
    int i2c_address;

    Gyro();
    Gyro(int address);
    
    int setup(); // power on gyro and do general setup
    void raw_acc(struct Acceleration* acc);
    void read_acc(struct Acceleration* acc);
    // Read the raw values from the gyro, accelerometer and temperature sensor.
    void read_all(struct RawSample* sample);
    
    void print_acc(struct Acceleration* acc);
    void print_all(struct RawSample* sample);
    
private:
    void request_data(unsigned int start, int len);
};


#endif
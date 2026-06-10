#include "Gyrosensor.h"

void Gyro::print_acc(struct Acceleration *acc) {
    Serial.print("Accelerometer: ");
    Serial.print("x= ");
    Serial.print(acc->x);
    Serial.print(", y= ");
    Serial.print(acc->y);
    Serial.print(", z= ");
    Serial.println(acc->z);
}

void Gyro::print_all(struct Gyro_RawSample *sample) {
  Serial.println("--- Raw Gyro Readings ---");
  print_acc(&sample->acc);

  Serial.print("Gyroscope:");
  Serial.print("x=");
  Serial.print(sample->gyro.x);
  Serial.print(", y= ");
  Serial.print(sample->gyro.y);
  Serial.print(", z= ");
  Serial.println(sample->gyro.z);
  Serial.println("");
}

void Gyro::request_data(unsigned int start, int len) {
    Wire.beginTransmission(i2c_address);
    Wire.write(start);
    Wire.endTransmission(false);
    Wire.requestFrom(i2c_address, len, true);
}

struct Gyro_RawSample Gyro::read_all() {

    struct Gyro_RawSample sample;
    request_data(GYRO_REG_ACC_START, 14);

    // consume accelerometer readings
    sample.acc.x = (Wire.read() << 8) | Wire.read();
    sample.acc.y = (Wire.read() << 8) | Wire.read();
    sample.acc.z = (Wire.read() << 8) | Wire.read();
    // consume temperature readings
    sample.temp = (Wire.read() << 8) | Wire.read();
    // consume gyro readings
    sample.gyro.x = (Wire.read() << 8) | Wire.read();
    sample.gyro.y = (Wire.read() << 8) | Wire.read();
    sample.gyro.z = (Wire.read() << 8) | Wire.read();

    return sample;
}

struct Acceleration Gyro::read_acc() {
    struct Acceleration acc;
    request_data(GYRO_REG_ACC_START, GYRO_REG_ACC_SIZE);

    acc.x = (Wire.read() << 8) | Wire.read();
    acc.y = (Wire.read() << 8) | Wire.read();
    acc.z = (Wire.read() << 8) | Wire.read();

    return acc;
}
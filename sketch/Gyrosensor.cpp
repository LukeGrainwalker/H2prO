#include "Gyrosensor.hpp"

Gyro::Gyro() {
    i2c_address = GYRO_DEFAULT_ADDR;
}

Gyro::Gyro(int address) {
    i2c_address = address;
}

int Gyro::setup() {

    Wire.begin();

    Wire.beginTransmission(i2c_address);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0x00); // wake up MPU6050 (set sleep = 0)
    Wire.endTransmission(true);
    
    Wire.beginTransmission(i2c_address); // set accelerometer range to ±2g
    Wire.write(0x1C); // ACCEL_CONFIG register
    Wire.write(0x00); // +-2g range
    Wire.endTransmission(true);
}

void Gyro::print_acc(struct Acceleration *acc) {
    Serial.print("Accelerometer: ");
    Serial.print("x= ");
    Serial.print(acc->x);
    Serial.print(", y= ");
    Serial.print(acc->y);
    Serial.print(", z= ");
    Serial.println(acc->z);
}

void Gyro::print_all(struct RawSample *sample) {
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

void Gyro::read_all(struct RawSample* sample) {

    request_data(GYRO_REG_ACC_START, 14);

    // consume accelerometer readings
    sample->acc.x = (Wire.read() << 8) | Wire.read();
    sample->acc.y = (Wire.read() << 8) | Wire.read();
    sample->acc.z = (Wire.read() << 8) | Wire.read();

    // consume temperature readings
    sample->temp = (Wire.read() << 8) | Wire.read();

    // consume gyro readings
    sample->gyro.x = (Wire.read() << 8) | Wire.read();
    sample->gyro.y = (Wire.read() << 8) | Wire.read();
    sample->gyro.z = (Wire.read() << 8) | Wire.read();
}

void Gyro::raw_acc(struct Acceleration* acc) {
    request_data(GYRO_REG_ACC_START, GYRO_REG_ACC_SIZE);

    acc->x = (Wire.read() << 8) | Wire.read();
    acc->y = (Wire.read() << 8) | Wire.read();
    acc->z = (Wire.read() << 8) | Wire.read();

    return acc;
}

void Gyro::read_acc(struct Acceleration* acc) {
    int32_t x, y, z; x = y = z = 0;
    acc->x = 0, acc->y = 0, acc->z = 0;

    for (int i = 0; i < 10; i++) {
        raw_acc(acc);
        x += acc->x;
        y += acc->y;
        z += acc->z;

        delay(2);
    }

    acc->x = x / 10;
    acc->y = y / 10;
    acc->z = z / 10;
}
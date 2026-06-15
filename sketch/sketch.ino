#include <Wire.h>

#include <H2prO.hpp>

#define MPU_ADDR 0x68  // Default I2C address of MPU6050
#define ACC_RANGE 2 // +-2g
#define GYRO_RANGE 250 // +- 250°/s
#define GYRO_REG_ACC_START 0x3B // start register for acceleration data
#define GYRO_REG_ACC_SIZE 6
#define GYRO_REG_GYRO_START 0x43 // start register for gyroscope data
#define GYRO_REG_GYRO_SIZE 6
#define GYRO_REG_TEMP_START 0x41 // start register for temperature data
#define GYRO_REG_TEMP_SIZE 2

#define ROLL_BASE 90

/*
// Wiring for MPU6050:
// Sensor | Arduino UNO
//  VCC   ->  3.3V
//  GND   ->  GND
//  SCL   ->  A5
//  SDA   ->  A4
//  AD0   ->  GND
*/

struct Acceleration {
  int16_t x, y, z;
};

struct Gyroscope {
  int16_t x, y, z;
};

struct Gyro_RawSample {
  float temp;
  struct Acceleration acc;
  struct Gyroscope gyro;
};

void gyro_print_acc(struct Acceleration* acc);
void gyro_print_all(struct Gyro_RawSample* sample);
void gyro_request_data(unsigned int start, int len);

void gyro_request_data(unsigned int start, int len) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(start);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, len, true);
}

/*
 * Read the raw values from the gyro, accelerometer and temperature sensor.
 */
struct Gyro_RawSample gyro_read_all() {

  struct Gyro_RawSample sample;
  gyro_request_data(GYRO_REG_ACC_START, 14);

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

struct Acceleration gyro_read_acc() {

  struct Acceleration acc;
  gyro_request_data(GYRO_REG_ACC_START, GYRO_REG_ACC_SIZE);

  acc.x = (Wire.read() << 8) | Wire.read();
  acc.y = (Wire.read() << 8) | Wire.read();
  acc.z = (Wire.read() << 8) | Wire.read();

  return acc;
}

void gyro_print_all(struct Gyro_RawSample* sample) {
  Serial.println("--- Raw Gyro Readings ---");
  gyro_print_acc(&sample->acc);

  Serial.print("Gyroscope:");
  Serial.print("x=");
  Serial.print(sample->gyro.x);
  Serial.print(", y= ");
  Serial.print(sample->gyro.y);
  Serial.print(", z= ");
  Serial.println(sample->gyro.z);
  Serial.println("");
}

void gyro_print_acc(struct Acceleration* acc) {
  Serial.print("Accelerometer: ");
  Serial.print("x= ");
  Serial.print(acc->x);
  Serial.print(", y= ");
  Serial.print(acc->y);
  Serial.print(", z= ");
  Serial.println(acc->z);
}

void avg_samples(struct Acceleration* dst, struct Acceleration* src_arr, int len) {
  dst->x = dst->y = dst->z = 0;

  for (int i = 0; i < len; i++) {
    dst->x += src_arr[i].x;
    dst->y += src_arr[i].y;
    dst->z += src_arr[i].z;
  }

  dst->x = dst->x / len;
  dst->y = dst->y / len;
  dst->z = dst->z / len;
}

/*
what is drinking?
roll base = -90°
stationary = -110° - -75°
drinking = -110° - -180°, 90° - 180°, -75° - 135°

roll base = 90°
stationary = 75° - 110°
drinking = -100° - 75°, -90° - 110°
*/
bool is_drinking() {
  float ax, ay, az;
  float roll = 0;
  struct Acceleration acc_data;

  for (int i = 0; i < 10; i++) {
    acc_data = gyro_read_acc();

    ax = acc_data.x;
    az = acc_data.z;
    roll += atan2(-ax, az) * 180 / PI;
    delay(2);
  }

  roll = roll / 10;

  //
  if (ROLL_BASE > 0) {
    if (roll >= 75 && roll <= 110) {
      return false;
    }
  } else {
    if (roll >= -110 && roll <= -75) {
      return false;
    }
  }

  return true;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);           // PWR_MGMT_1 register
  Wire.write(0x00);           // Wake up MPU6050 (set sleep = 0)
  Wire.endTransmission(true);

  // Set accelerometer range to ±2g (most stable)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);           // ACCEL_CONFIG register
  Wire.write(0x00);           // ±2g range
  Wire.endTransmission(true);

  Serial.println("MPU6050 Initialized for Raw Accelerometer Readings");
}

void loop() {
  if (is_drinking()) {
    Serial.println("Is Driking!!!");
  }

  //float pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180 / PI;
  delay(200);
}

#include <Wire.h>
#include <Gyrosensor.h>

#define MPU_ADDR 0x68 // Default I2C address of MPU6050

void setup() {
    Wire.begin();
    Serial.begin(9600);

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0x00); // Wake up MPU6050 (set sleep = 0)
    Wire.endTransmission(true);

    // Set accelerometer range to ±2g (most stable)
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x1C); // ACCEL_CONFIG register
    Wire.write(0x00); // ±2g range
    Wire.endTransmission(true);

    Serial.println("MPU6050 Initialized.");
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

void loop() {
    if (is_drinking()) {
        Serial.println("Is Driking!!!");
    }

    delay(200);
}
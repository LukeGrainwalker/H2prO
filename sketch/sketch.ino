#include <Wire.h>
#include "Gyrosensor.hpp"

#define MPU_ADDR 0x68 // default I2C address of MPU6050
#define DEFAULT_ROLLBASE 90

Gyro gyro = Gyro();

enum STATE {
    LED_IDLE = 0,
    LED_DRINKING,
    LED_WARNING,
    LED_ALERT
};

struct TimeThreshold {
    int lower, higher;
};

int RED = 9;
int GREEN = 10;
int BLUE = 11;
int BUZZER_PIN = 8;

enum STATE led_state = LED_IDLE;
unsigned long last_hydration;
unsigned int time_diff;
bool started_drinking = false;
struct TimeThreshold warningThres;
struct TimeThreshold alertThres;


void setup() {
    Serial.begin(9600);

    gyro.setup();
    Serial.println("MPU6050 Initialized.");
    
    last_hydration = millis();
    //warningThres = { .lower = 30, .higher = 60};
    //alertThres = { .lower = 60, .higher = 90};
    warningThres = { .lower = 2*60, .higher = 3*60};
    alertThres = { .lower = 3*60, .higher = 5*60};
}

/*
what is drinking?

The gyro can either be mounted with the x axis pointing downwards or upwards.
Depending on the orientation of the sensor the roll is 90° or -90°.
Therefore we need to adjust the angles that correspond to the sensor being stationary (e. g. on the desk).
Drinking means the angle measured is outside of the specified range of stationary.

When the x axis is pointing upwards:
    roll base = -90°
    stationary = -110° - -75°

When the x axis is pointing downwards (preferred):
    roll base = 90° (x axis is pointing downwards)
    stationary = 75° - 110°
*/
bool is_drinking() {
    float roll = 0;
    struct Acceleration acc_data;

    gyro.read_acc(&acc_data);
    gyro.print_acc(&acc_data);
    roll = atan2(-acc_data.x, acc_data.z) * 180 / PI;

    //Serial.print("roll: ");
    //Serial.println(roll);

    if (DEFAULT_ROLLBASE > 0) {
        if (roll >= 60 && roll <= 130) return false;
    } else {
        if (roll >= -110 && roll <= -75) return false;
    }

    return true;
}

unsigned int get_seconds(unsigned long time) {
    return (time / 1000);
}

void set_led_color(int r, int g, int b) {
    analogWrite(RED, r);
    analogWrite(GREEN, g);
    analogWrite(BLUE, b);
}

void loop() {
    if (is_drinking()) {
        if (led_state != LED_DRINKING) {
            led_state = LED_DRINKING;
            set_led_color(0, 255, 0);
        }

        if (!started_drinking) {
            last_hydration = millis();
            started_drinking = true;
        }

    } else {
        if (started_drinking) {
            started_drinking = false;
            last_hydration = millis();

            if (led_state != LED_IDLE) {
                led_state = LED_IDLE;
                set_led_color(0, 0, 255);
            }
        }

        time_diff = get_seconds(millis()) - get_seconds(last_hydration);
        if (time_diff >= warningThres.lower && time_diff < warningThres.higher) {
            // WARNING
            if (led_state != LED_WARNING) {
                set_led_color(255, 255, 0);
                led_state = LED_WARNING;
            }
        } else if (time_diff >= alertThres.lower && time_diff < alertThres.higher) {
            // ALERT
            if (led_state != LED_ALERT) {
                set_led_color(255, 0, 0);
                led_state = LED_ALERT;
            }
            // move servo
        } else {
            // DIE
        }
    }
}
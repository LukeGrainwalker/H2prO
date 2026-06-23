#include <Wire.h>
#include "Util.hpp"
#include "LED.hpp"
#include "Gyrosensor.hpp"
#include "pitches.h"

#define MPU_ADDR 0x68 // default I2C address of MPU6050
enum STATE { LED_IDLE = 0, LED_DRINKING, LED_WARNING, LED_ALERT };
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

Gyro gyro = Gyro();
NormalizedVector base_vec = NormalizedVector(-GYRO_1G, 0, 0);
RGBLed rgb_led = RGBLed(RED, GREEN, BLUE, Color(0, 0, 255), COMMON_ANODE);

void setup() {
  Serial.begin(9600);

  rgb_led.update();
  //gyro.setup();
  Serial.println("MPU6050 Initialized.");

  last_hydration = millis();
  // warningThres = { .lower = 30, .higher = 60};
  // alertThres = { .lower = 60, .higher = 90};
  warningThres = {.lower = 2 * 60, .higher = 3 * 60};
  alertThres = {.lower = 3 * 60, .higher = 5 * 60};
}

/*
what is drinking?
*/
bool is_drinking() {
  float roll = 0;
  struct Acceleration acc_data;

  gyro.read_acc(&acc_data);

  NormalizedVector vec = NormalizedVector(
    acc_data.x,
    acc_data.y,
    acc_data.z
  );

  double angle = vec.scalar_multiply(&base_vec) * 180 / PI;

  if (angle >= 45) {
    return true;
  }

  return false;
}

unsigned int get_seconds(unsigned long time) {
  return (time / 1000);
}

void loop() {
  if (/*is_drinking()*/false) {
    rgb_led.ensure_state(LED_DRINKING, Color(0, 255, 0));
  
    if (!started_drinking) {
      last_hydration = millis();
      started_drinking = true;
    }
  } else {
    if (started_drinking) {
      started_drinking = false;
      last_hydration = millis();

      rgb_led.ensure_state(LED_IDLE, Color(0, 0, 255));
    }

    time_diff = get_seconds(millis()) - get_seconds(last_hydration);
    if (time_diff >= warningThres.lower && time_diff < warningThres.higher) {
      // WARNING
      rgb_led.ensure_state(LED_WARNING, Color(255, 255, 0));
    } else if (time_diff >= alertThres.lower && time_diff < alertThres.higher) {
      // ALERT
      rgb_led.ensure_state(LED_ALERT, Color(255, 0, 0));
      // move servo
    } else {
      // DIE
    }
  }

  /* tone(7, NOTE_A3, 250);
  delay(50);
  tone(7, NOTE_E4, 500);
  delay(100);
  tone(7, NOTE_B3, 250);
  delay(50);
  tone(7, NOTE_E4, 250);
  delay(50); */

  delay(1000);

}

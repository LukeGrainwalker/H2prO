#include <Wire.h>
#include "H2prO.hpp"
#include "Util.hpp"
#include "LED.hpp"
#include "Sequence.hpp"
#include "Gyrosensor.hpp"
#include "Action.hpp"
#include "pitches.h"

#define MPU_ADDR 0x68 // default I2C address of MPU6050
enum STATE { LED_IDLE = 0, LED_DRINKING, LED_WARNING, LED_ALERT };
struct TimeThreshold {
  int lower, higher;
};

int BUZZER_PIN = 2;
int BUZZER_GND = 4;

enum STATE led_state = LED_IDLE;
unsigned long last_hydration;
unsigned int time_diff;
bool started_drinking = false;
unsigned long time = 0;
struct TimeThreshold warningThres;
struct TimeThreshold alertThres;

Color RGB_RED = Color(255, 0, 0);
Color RGB_GREEN = Color(0, 255, 0);
Color RGB_BLUE = Color(0, 255, 0);
Color RGB_BLACK = Color(0, 0, 0);

Color RGB_ORANGE = Color(255, 153, 0);
Color RGB_PURPLE = Color(128, 0, 128);
Color RGB_PINK = Color(255, 0, 255);
Color RGB_LIGHTGREEN = Color(51, 204, 51);
Color RGB_TURQUOISE = Color(64, 224, 208);

SequenceItem drink_animation_items[] = {
  {300, &RGB_GREEN},
  {100, &RGB_ORANGE},
  {100, &RGB_TURQUOISE},
  {100, &RGB_PURPLE},
  {100, &RGB_PINK},
  {100, &RGB_LIGHTGREEN},
};
Sequence drink_animation = Sequence(drink_animation_items, 6, true);

SequenceItem alarm_tones[] = {
  {250, &NOTE_A3},
  {500, &NOTE_E4},
  {250, &NOTE_B3},
  {250, &NOTE_E4},
  {1000, (int*)0}
};
Sequence alarm_seq = Sequence(alarm_tones, 5, true);

Gyro gyro = Gyro();
NormalizedVector base_vec = NormalizedVector(0, -GYRO_1G, 0);
RGBLed rgb_led = RGBLed(9, 10, 11, Color(0, 0, 255), COMMON_ANODE);

//LED lsd_led = LED(8);
//H2prO h2pro = H2prO();

void setup() {
  Serial.begin(9600);

  rgb_led.update();
  gyro.setup();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUZZER_GND, OUTPUT);
  digitalWrite(BUZZER_GND, LOW);
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
  //gyro.print_acc(&acc_data);

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

int current_tone = 0;

void loop() {
  time = millis();

  if (is_drinking()) {
    struct SequenceItem* next_color = drink_animation.getby_time(time);
    if (next_color != nullptr) {
      rgb_led.ensure_color((Color*)next_color->data);
    }
  
    last_hydration = time;
    started_drinking = true;
  } else {
    if (started_drinking) {
      noTone(BUZZER_PIN);

      started_drinking = false;
      last_hydration = time;
      rgb_led.ensure_state(LED_IDLE, Color(0, 0, 255));
    }

    time_diff = get_seconds(millis()) - get_seconds(last_hydration);
    if (time_diff >= warningThres.lower && time_diff < warningThres.higher) {
      // WARNING
      rgb_led.ensure_state(LED_WARNING, Color(255, 255, 0));
    } else if (time_diff >= alertThres.lower && time_diff < alertThres.higher) {
      // ALERT
      rgb_led.ensure_state(LED_ALERT, Color(255, 0, 0));

      int freq;
      struct SequenceItem* next_tone = alarm_seq.getby_time(time);
      if (next_tone != nullptr) {
        freq = *(int*)next_tone->data;
        if (freq != current_tone) {
          tone(BUZZER_PIN, freq, next_tone->duration);
        }
      }
      // move servo
    } else {
      // DIE
    }
  }

}

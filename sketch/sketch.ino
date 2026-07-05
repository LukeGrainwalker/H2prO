#include <Wire.h>
#include <Servo.h>
#include "H2prO.hpp"
#include "Util.hpp"
#include "LED.hpp"
#include "Sequence.hpp"
#include "Gyrosensor.hpp"
#include "Output.hpp"
#include "pitches.h"

SequenceItem drink_animation[] = {
  {150, (void*)&RGB_GREEN},
  {150, (void*)&RGB_TURQUOISE},
  {150, (void*)&RGB_PURPLE},
  {150, (void*)&RGB_PINK},
  {150, (void*)&RGB_LIGHTGREEN, .last=true}
};

SequenceItem disappointed_animation[] = {
  {500, (void*)&RGB_RED},
  {250, (void*)&RGB_BLACK, .last=true},
};

SequenceItem anxious_sound[] = {
  {100, (void*)&NOTE_E5},
  {100, (void*)&NOTE_F5},
  {100, (void*)&NOTE_E5},
  {100, (void*)&NOTE_DS5},
  {100, (void*)&NOTE_E5, .last=true}
};

SequenceItem surprised_sound[] = {
  {100, (void*)&NOTE_C5},
  {100, (void*)&NOTE_G5},
  {100, (void*)&NOTE_C6},
  {100, (void*)&NOTE_B5, .last=true}
};

SequenceItem impressed_sound[] = {
  {200, (void*)&NOTE_C5},
  {250, (void*)&NOTE_G5},
  {150, (void*)&NOTE_C6},
  {200, (void*)&NOTE_B5, .last=true}
};

SequenceItem alarm_tones[] = {
  {250, (void*)&NOTE_A3},
  {500, (void*)&NOTE_E4},
  {250, (void*)&NOTE_B3},
  {250, (void*)&NOTE_E4},
  {1000, (void*)&NOTE_PAUSE, .last=true}
};

int BUZZER_PIN = 2;
int BUZZER_GND = 4;

bool started_drinking = false;
unsigned long time = 0;

Gyro gyro = Gyro();
NormalizedVector base_vec = NormalizedVector(0, -GYRO_1G, 0);
RGBLed rgb_led = RGBLed(9, 10, 11, Color(0, 0, 255), COMMON_ANODE);
Buzzer buzzer = Buzzer();
H2prO h2pro = H2prO(60);
Output outputs = Output();
Sequence* all_sequences[SEQUENCE_MAX];

void setup() {

  Serial.begin(9600);
  gyro.setup();
  Serial.println("MPU6050 Initialized.");

  rgb_led.update();
  buzzer.init(BUZZER_PIN);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUZZER_GND, OUTPUT);
  digitalWrite(BUZZER_GND, LOW);

  all_sequences[SEQUENCE_ALARM] = new Sequence(alarm_tones, true, 50);
  all_sequences[SEQUENCE_DRINK] = new Sequence(drink_animation, true);
  all_sequences[SEQUENCE_DISAPP] = new Sequence(disappointed_animation, true);
  all_sequences[SEQUENCE_ANXIOUS_SOUND] = new Sequence(anxious_sound, false, 25);
  all_sequences[SEQUENCE_IMPRESSED_SOUND] = new Sequence(impressed_sound, false, 25);
  all_sequences[SEQUENCE_SURPRISED_SOUND] = new Sequence(surprised_sound, false, 25);
  outputs.init(all_sequences, &rgb_led, &buzzer);
  h2pro.set_hydration(millis());
}

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

enum action current_action = NONE;
int drink_jitter = 250;
unsigned long drink_time = 0;
bool started_lifting = false;

void loop() {
  time = millis();

  if (is_drinking()) {
    if (!started_lifting) {
      drink_time = millis();
      started_lifting = true;
    }

    if ((millis() - drink_time) > drink_jitter) {
      started_drinking = true;
      current_action = DRINK;
    }

  } else {
    if (started_drinking) {
      h2pro.set_hydration(time);
      started_drinking = false;
      started_lifting = false;
      current_action = NONE;
    }
  }

  enum emotion em = h2pro.process(current_action, time);
  outputs.process_emotion(em);
  outputs.update(time);
  
}

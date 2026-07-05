#include "Output.hpp"
#include "H2prO.hpp"
#include "colors.hpp"
#include "sequences.hpp"

void Output::init(Sequence** _sequences, RGBLed* _rgb_led, Buzzer* _buzzer) {
    sequences = _sequences;
    rgb_led = _rgb_led;
    buzzer = _buzzer;
}

int Output::process_emotion(enum emotion em) {
    if (em == current_emotion) {
        return 0;
    }

    rgb_led_seq = nullptr;
    buzzer_seq = nullptr;
    buzzer->stop();

    bool emotion_implemented = true;

    if (em == NORMAL) {
        rgb_led->ensure_color(&COLOR_NORMAL);
    } else if (em == ANXIOUS) {
        rgb_led->ensure_color(&COLOR_ANXIOUS);
        buzzer_seq = sequences[SEQUENCE_ANXIOUS_SOUND];
    } else if (em == ANGRY) {
        rgb_led->ensure_color(&COLOR_ANGRY);
        buzzer_seq = sequences[SEQUENCE_ALARM];
        buzzer_seq->reset();
        buzzer->play();
    } else if (em == HAPPY) {
        rgb_led->ensure_color(&RGB_GREEN);
    } else if (em == DISAPPOINTED) {
        rgb_led_seq = sequences[SEQUENCE_DISAPP];
        rgb_led_seq->reset();
    } else if (em == IMPRESSED) {
        buzzer_seq = sequences[SEQUENCE_IMPRESSED_SOUND];
        rgb_led_seq = sequences[SEQUENCE_DRINK];
        rgb_led_seq->reset();
    } else if (em == SURPRISED) {
        rgb_led->ensure_color(&RGB_GREEN);
        buzzer_seq = sequences[SEQUENCE_SURPRISED_SOUND];
    }  else {
        emotion_implemented = false;
    }

    if (emotion_implemented) {
        current_emotion = em;
        if (buzzer_seq != nullptr) {
            buzzer_seq->reset();
            buzzer->play();
        }
    }
}

void Output::update_buzzer(unsigned long time) {
    if (buzzer_seq == nullptr) return;
    
    struct SequenceItem *next_tone = buzzer_seq->getby_time(time);
    if (next_tone == nullptr) return;

    int freq = *(int*)next_tone->data;
    buzzer->ensure_tone(freq, next_tone->duration);

}

void Output::update_rgb_led(unsigned long time) {
    if (rgb_led_seq == nullptr) return;

    struct SequenceItem *next = rgb_led_seq->getby_time(time);
    if (next == nullptr) return;

    const Color* color = (const Color*)next->data;
    rgb_led->ensure_color(color);
}

void Output::update(unsigned long time) {
    update_rgb_led(time);
    update_buzzer(time);
}


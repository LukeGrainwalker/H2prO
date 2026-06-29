#include "H2prO.hpp"

enum emotion H2prO::process(enum action a, unsigned long time) {
	int time_over;
	unsigned int deltat = (time - last_hydration) / 1000;

	switch(a) {
		case LIFT: // ... not yet implemented
			if (deltat > 60*10) {
				device_emotion = SCEPTICAL;
			} else {
				device_emotion = INTERESTED;
			}
			break;
		case DRINK:

			// still drinking?
			if (a == last_action) {
				return last_emotion;
			}
			
			time_over = deltat - ideal;
			/* Serial.print("time_over= ");
			Serial.println(time_over);
			Serial.print("deltat= ");
			Serial.println(deltat); */

			if (time_over > 60*5) {
				device_emotion = DISAPPOINTED;
			} else if (time_over > -ideal20 && time_over < -ideal10) {
				device_emotion = SURPRISED;
			} else if (time_over >= -ideal10 && time_over <= 0) {
				device_emotion = IMPRESSED;
			} else {
				device_emotion = HAPPY;
			}
			break;
		default:
			if (deltat > ideal*2) {
				device_emotion = ANGRY;
			} else if (deltat > ideal) {
				device_emotion = ANXIOUS;
			} else {
				device_emotion = NORMAL;
			}
	}

	last_emotion = device_emotion;
	last_action = a;

	return device_emotion;
}

void H2prO::set_hydration(unsigned long time) {
	last_hydration = time;
}

Color H2prO::emotion_to_color(enum emotion e){
	switch(e) {
		case SCEPTICAL:
			return Color(153, 5, 252);
		case INTERESTED:
			return Color(244, 252, 5);
		case DISAPPOINTED:
			return Color(108, 0, 132);
		case IMPRESSED:
			return Color(233, 255, 0);
		case SURPRISED:
			return Color(16, 0, 255);
		case ANGRY:
			return Color(255, 0, 0);
		case ANXIOUS:
			return Color(165, 0, 255);
		case SUPPORTIVE:
			return Color(29, 255, 0);
		case NORMAL:
		default:
			return Color(0, 0, 255);
	}

}

void H2prO::print_emotion(enum emotion e) {
	if (e == ANGRY) {
		Serial.print("ANGRY");
	} else if (e == HAPPY) {
		Serial.print("HAPPY");
	} else if (e == FRUSTRATED) {
		Serial.print("FRUSTRATED");
	} else if (e == NORMAL) {
		Serial.print("NORMAL");
	} else if (e == INTERESTED) {
		Serial.print("INTERESTED");
	} else if (e == DISAPPOINTED) {
		Serial.print("DISAPPOINTED");
	} else if (e == SURPRISED) {
		Serial.print("SURPRISED");
	} else if (e == ANXIOUS) {
		Serial.print("ANXIOUS");
	} else if (e == SUPPORTIVE) {
		Serial.print("SUPPORTIVE");
	} else if (e == IMPRESSED) {
		Serial.print("IMPRESSED");
	} else if (e == SCEPTICAL) {
		Serial.print("SCEPTICAL");
	} else {
		Serial.print("UNKOWN EMOTION");
	}
}
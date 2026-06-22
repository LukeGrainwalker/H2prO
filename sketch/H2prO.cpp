#include "H2prO.hpp"

enum emotion H2prO::process(enum action a, float time) {
	float deltat = drink_time - ideal;
	switch(a) {
		case LIFT:
			if (deltat > 60*10) {
				device_emotion = SCEPTICAL;
			} else {
				device_emotion = INTERESTED;
			}
			break;
		case DRINK:
			if (deltat > 60*5) {
				device_emotion = DISAPOINTED;
			} else if (deltat > -10 && deltat < 10)  {
				device_emotion = IMPRESSED;
			} else if (deltat < 0){
				device_emotion = SUPRISED;
			} else {
				device_emotion = DEFAULT;
			}
			drink_time = 0.0;
			break;
		default:
			drink_time += time;
			if (deltat > 30*3) {
				device_emotion = ANGRY;
			} else if (deltat > 60) {
				device_emotion = ANXIOUS;
			} else if (deltat > 30) {
				device_emotion = SUPORTIVE;
			} else {
				device_emotion = DEFAULT;
			}
	}
	return device_emotion;
}

float H2prO::getTime() {
	return drink_time;
}

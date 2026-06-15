#include "H2prO.hpp"


enum emotion H2prO::process(enum action a, float time) {
	switch(a) {
		case LIFT:
			device_emotion = INTERESTED;
			break;
		case DRINK:
			if (drink_time > 200) {
				device_emotion = DISAPOINTED;
			} else {
				device_emotion = HAPY;
			}
			drink_time = 0.0;
			break;
		default:
			drink_time += time;
	}
	return device_emotion;
}


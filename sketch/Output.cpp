#include "H2prO.hpp"
#include <Arduino.h>
#include "Output.hpp"

int setEmotion(enum emotion e){
	switch(e){
		case SCEPTICAL:
			return 0x9905fc;
			break;
		case INTERESTED:
			return 0xf4fc05;
			break;
		case DISAPPOINTED:
			return 0x6c0084;
			break;
		case IMPRESSED:
			return 0xe9ff00;
			break;
		case SURPRISED:
			return 0x1000ff;
			break;
		case ANGRY:
			return 0xff0000;
			break;
		case ANXIOUS:
			return 0xa500ff;
			//buzzing = true;
			break;
		case SUPPORTIVE:
			return 0x1dff00;
			break;
		case DEFAULT_EMOTION: default: 
			return 0;
			break;
	}

}

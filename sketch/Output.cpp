#include "H2prO.hpp"
#include <Arduino.h>
#include "Output.hpp"

Output::setEmotion(enum emotion e){
	switch(e){
		case SCEPTICAL:
			color = 0x9905fc;
			break;
		case INTERESTED:
			color = 0xf4fc05;
			break;
		case DISAPOINTED:
			color = 0x6c0084;
			break;
		case IMPRESSED:
			color = 0xe9ff00;
			break;
		case SUPRISED:
			color = 0x1000ff;
			break;
		case ANGRY:
			color = 0xff0000;
			break;
		case ANXIOUS:
			color = 0xa500ff;
			buzzing = true;
			break;
		case SUPORTIVE:
			color = 0x1dff00;
			break;
		case DEFAULT: default: 
			color = 0;
			break;
	}
	analogWrite(pinr, color & 0xff);
	analogWrite(ping, (color >> 8) & 0xff);
	analogWrite(pinb, (color >> 16) & 0xff);

}

#include <H2prO.hpp>
#include <Arduino.h>
#include <Output.hpp>

Output::setEmotion(enum emotion e){
	switch(e){
		case DEFAULT: default: 
			color = 0;
			break;
	}
	analogWrite(pinr, color & 0xff);
	analogWrite(ping, (color >> 8) & 0xff);
	analogWrite(pinb, (color >> 16) & 0xff);

}

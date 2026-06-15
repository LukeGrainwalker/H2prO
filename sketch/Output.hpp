
class Output{
	privete:
		int color;
		bool buzzing;
		int pinr;
		int ping;
		int binb;
	public:
		int setEmotion(enum emotion e);
		Output(int pr, int pg, int pb) {
			pinr = pr;
			ping = pg;
			pinb = pb;
			pinMode(pinr, OUTPUT);
			pinMode(ping, OUTPUT);
			pinMode(pinb, OUTPUT);
		}
}



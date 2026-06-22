
class Output{
	private:
		int color;
		bool buzzing;
		int pinr;
		int ping;
		int pinb;
	public:
		int setEmotion(enum emotion e);
		Output(int pr, int pg, int pb) {
			this->pinr = pr;
			this->ping = pg;
			this->pinb = pb;
			pinMode(pinr, OUTPUT);
			pinMode(ping, OUTPUT);
			pinMode(pinb, OUTPUT);
		}
};



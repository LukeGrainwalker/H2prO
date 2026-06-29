#ifndef H2PRO_HPP
#define H2PRO_HPP

/* #include "Util.hpp" */
#include "LED.hpp"

enum action {
	NONE = -1,
	DRINK,
	LIFT,
};

enum emotion {
	NORMAL = -1,
	ANGRY,
	HAPPY,
	FRUSTRATED,
	INTERESTED,
	DISAPPOINTED,
	SURPRISED,
	ANXIOUS,
	SUPPORTIVE,
	IMPRESSED,
	SCEPTICAL
};

struct TimeThreshold {
  int lower, higher;
};

class H2prO {
	public:
		H2prO(unsigned int ideal_time) {
			ideal = ideal_time;
			ideal20 = (int)ideal_time*0.2;
			ideal10 = (int)ideal_time*0.1;
			last_emotion = NORMAL;
			last_action = NONE;
		}

		enum emotion process(enum action a, unsigned long time);
		void set_hydration(unsigned long time);
		Color emotion_to_color(enum emotion e);
		void print_emotion(enum emotion e);
	private:
		enum emotion device_emotion;
		unsigned long last_hydration;
		enum emotion last_emotion;
		enum action last_action;
		unsigned int ideal;
		int ideal20;
		int ideal10;
};


#endif
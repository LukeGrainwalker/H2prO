#ifndef H2PRO_HPP
#define H2PRO_HPP

enum action{
	NONE,
	DRINK,
	LIFT,
};

enum emotion {
	ANGRY,
	HAPPY,
	FRUSTRATED,
	DEFAULT_EMOTION,
	INTERESTED,
	DISAPPOINTED,
	SURPRISED,
	ANXIOUS,
	SUPPORTIVE,
	IMPRESSED,
	SCEPTICAL
};

class H2prO {
	public:
		enum emotion device_emotion = DEFAULT_EMOTION;
		enum emotion process(enum action a, unsigned long time);
		float getTime();
		H2prO(float ideal_time) {
			ideal = ideal_time;
		}
	private:
		float drink_time;
		float ideal;
};

#endif
enum action{
	NONE,
	DRINK,
	LIFT,
};

enum emotion {
	ANGRY,
	HAPPY,
	FRUSTRATED,
	DEFAULT,
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
		enum emotion device_emotion = DEFAULT;
		enum emotion process(enum action, float time);
		float getTime();
		H2prO(float ideal_time) {
			ideal = ideal_time;
		}
	private:
		float drink_time;
		float ideal;
};




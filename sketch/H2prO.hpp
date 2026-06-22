enum action{
	NONE,
	DRINK,
	LIFT,
};

enum emotion {
	ANGRY,
	HAPY,
	FRUSTRATED,
	DEFAULT_EMOTION,
	INTERESTED,
	DISAPOINTED,
	SUPRISED,
	ANXIOUS,
	SUPORTIVE,
	IMPRESSED,
	SCEPTICAL
};

class H2prO {
	public:
		enum emotion device_emotion = DEFAULT_EMOTION;
		enum emotion process(enum action, float time);
		float getTime();
		H2prO(float ideal_time) {
			ideal = ideal_time;
		}
	private:
		float drink_time;
		float ideal;
};
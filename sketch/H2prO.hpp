enum action{
	NONE,
	DRINK,
	LIFT,
};

enum emotion {
	ANGRY,
	HAPY,
	FRUSTRATED,
	SAD,
	TIRED,
	DEFAULT,
	INTERESTED,
	DISAPOINTED,
};

class H2prO {
	public:
		enum emotion device_emotion = DEFAULT;
		enum emotion process(enum action, float time);
	private:
		float drink_time;
};




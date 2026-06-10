#include "H2prO.hpp"


class H2prO {
	public:
		enum emotion device_emotion;
		enum emotion process(enum action, float time);
};

enum emotion H2prO::process(enum action, float time) {
	return DEFAULT;
}


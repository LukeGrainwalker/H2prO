#include <iostream>
#include <H2prO.hpp>
using namespace std;

bool testH2prO(H2prO& obj, enum action a, float time, enum emotion e){
	enum emotion ret = obj.process(a, time);
	bool correct;
	if ( ret == e ) {
		cout << "correct emotion: ";
		correct = true;
	}else{
		cout << "wrong emotion: ";
		correct = false;
	}

	switch (ret) {
		case SCEPTICAL:
			cout << "sceptical";
			break;
		case INTERESTED:
			cout << "interested";
			break;
		case DISAPPOINTED:
			cout << "disapointed";
			break;
		case SURPRISED:
			cout << "suprised";
			break;
		case IMPRESSED:
			cout << "impressed";
			break;
		case DEFAULT_EMOTION:
			cout << "default";
			break;
		case ANXIOUS:
			cout << "anxious";
			break;
		case SUPPORTIVE:
			cout << "suportive";
			break;
		case ANGRY:
			cout << "angry";
			break;
		default:
			cout << "none";
	}
	cout << " at: " << obj.getTime() << "s\n";
	return correct;
}

int main(int argc, char** argv){
	cout << "Unit tests: \n";
	H2prO test(15*60);
	//cout << (test.process(NONE, 10.0) == DEFAULT_EMOTION) << "\n";
	testH2prO(test, NONE, 3.0, DEFAULT_EMOTION);
	testH2prO(test, NONE, 6.0, DEFAULT_EMOTION);
	testH2prO(test, LIFT, 2.0, INTERESTED);
	testH2prO(test, DRINK, 2.0, SURPRISED);
	return 0;
}

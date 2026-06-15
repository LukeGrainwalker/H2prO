#include <iostream>
#include <H2prO.hpp>
using namespace std;

int main(int argc, char** argv){
	cout << "Unit tests: \n";
	H2prO test;
	cout << (test.process(NONE, 10.0) == DEFAULT) << "\n";
	return 0;
}

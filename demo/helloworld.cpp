#include "Engine.h"

#include <iostream>

void KeyIsDown(int key) {

}

int main(int argc, const char* argv[]) {
	using namespace lilengine;

	Engine e;
	e.Startup();
	e.RunGameLoop(NULL);
	e.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
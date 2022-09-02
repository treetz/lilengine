#include "Engine.h"

#include <iostream>

int main(int argc, const char* argv[]) {
	using namespace lilengine;

	Engine e;
	e.Startup();
	e.RunGameLoop();

	std::cout << "Hello, World!\n";
	return 0;
}
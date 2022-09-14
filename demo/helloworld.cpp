#pragma once

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"

#include <iostream>

using namespace lilengine;

void E_KeyIsPressed(Engine& e) {
	if (e.GetInputManager().KeyIsPressed(GLFW_KEY_E)) {
		std::cout << "The E key has been pressed!\n";
	}
}

int main(int argc, const char* argv[]) {
	Engine e;
	e.Startup();

	/* You can call RunGameLoop() with an empty lambda function if you don't
	 * want a callback function to be called:
	 *     e.RunGameLoop([]() {});
	 */

	e.RunGameLoop(E_KeyIsPressed);
	e.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
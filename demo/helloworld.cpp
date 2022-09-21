#pragma once

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

#include <iostream>

using namespace lilengine;

/* Basic User Input Testing */
void E_KeyIsPressed(Engine& e) {
	if (e.GetInputManager().KeyIsPressed(GLFW_KEY_E)) {
		std::cout << "The E key has been pressed!\n";
	}
}

/* Play a sound when the Spacebar is initially pressed */
bool pressed = false;

void PlayASound(Engine& e) {
	if (e.GetInputManager().GetKeyStatus(GLFW_KEY_SPACE) == GLFW_PRESS && pressed == false) {
		pressed = true;
		std::cout << "The Spacebar has been pressed!\n";
		//e.GetSoundManager().PlaySound("bubbles");
	}
	if (e.GetInputManager().GetKeyStatus(GLFW_KEY_SPACE) == GLFW_RELEASE && pressed == true) {
		pressed = false;
	}
}

int main(int argc, const char* argv[]) {
	Engine e;
	e.Startup();

	e.GetSoundManager().LoadSound("cheer", "cheer.wav");

	/*
	SoLoud::Soloud gSoloud;
	SoLoud::Wav gWave;

	gSoloud.init();

	int code = gWave.load("cheer.wav");

    std::cout << code << "\n";

	gSoloud.play(gWave);

	gSoloud.deinit();
	*/

	/* You can call RunGameLoop() with an empty lambda function if you don't
	 * want a callback function to be called:
	 *     e.RunGameLoop([]() {});
	 */
	e.RunGameLoop(PlayASound);
	e.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
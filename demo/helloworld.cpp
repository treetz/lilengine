#pragma once

#include <iostream>

#include "spdlog/spdlog.h"

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

using namespace lilengine;

// Print a message when the E key is pressed
void E_KeyIsPressed(Engine& e) {
	if (e.GetInputManager().KeyIsPressed(GLFW_KEY_E)) {
		spdlog::info("The E key has been pressed!\n");
	}
}

// Play a sound when the Spacebar is initially pressed
bool pressed = false;

void PlayASound(Engine& e) {
	if (e.GetInputManager().GetKeyStatus(GLFW_KEY_SPACE) == GLFW_PRESS && pressed == false) {
		pressed = true;
		e.GetSoundManager().PlaySound("cheer");
	}
	if (e.GetInputManager().GetKeyStatus(GLFW_KEY_SPACE) == GLFW_RELEASE && pressed == true) {
		pressed = false;
	}
}

// Draw multiple sprites
void DrawSprites(Engine &e) {
	Sprite s1;
	s1.image_name = "the_office";
	s1.position = vec3(10.f, 10.f, 0.f);
	s1.scale = vec3(10.f, 10.f, 0.f);
	s1.rotation = vec3(30.f, 0.f, 0.f);
	s1.z = 1.f;

	Sprite s2;
	s2.image_name = "explosion";

	const std::vector< Sprite >& sprites = { s1 };
	gEngine.GetGraphicsManager().Draw(sprites);
}

int main(int argc, const char* argv[]) {
	gEngine.Startup();

	gEngine.GetSoundManager().LoadSound("cheer", "cheer.wav");
	gEngine.GetGraphicsManager().LoadImage("the_office", "the_office.png");
	gEngine.GetGraphicsManager().LoadImage("explosion", "explosion.png");

	// You can call RunGameLoop() with an empty lambda function if you don't
	// want a callback function to be called:
	//     e.RunGameLoop([]() {});
	gEngine.RunGameLoop(DrawSprites);
	gEngine.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
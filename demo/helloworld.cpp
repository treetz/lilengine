#pragma once

#include <random>

#include <iostream>
#include "spdlog/spdlog.h"

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"
#include "ScriptingManager.h"
#include "TileMapManager.h"

using namespace lilengine;

// Callback function will run each iteration of the game loop
void UpdateCallback(Engine& e) {
	
}

int main(int argc, const char* argv[]) {
	// Start the engine
	gEngine.Startup();

	// Start the game loop
	gEngine.RunGameLoop(UpdateCallback);
	
	// Shutdown the engine
	gEngine.Shutdown();
	
	std::cout << "Hello, World!\n";
	return 0;
}
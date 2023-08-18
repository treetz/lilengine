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

void UpdateCallback(Engine& e) {
	
}

int main(int argc, const char* argv[]) {
	gEngine.Startup();

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();
	
	std::cout << "Hello, World!\n";
	return 0;
}
#pragma once

#include <iostream>

#include "spdlog/spdlog.h"

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"
#include "ScriptingManager.h"

using namespace lilengine;

void UpdateCallback(Engine& e) {

}

int main(int argc, const char* argv[]) {
	gEngine.Startup();

	// Load a game script.
	gEngine.GetScriptingManager().LoadScript("pong", "pong.lua");

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
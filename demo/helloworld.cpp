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
	ScriptingManager& scripting_manager = gEngine.GetScriptingManager();
	scripting_manager.LoadScript("pong_setup", "pong_setup.lua");
	scripting_manager.RunScript("pong_setup");

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
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

	//GraphicsManager& graphics_manager = gEngine.GetGraphicsManager();
	ECS& ecs = gEngine.GetECS();

	// Load up game scripts.
	ScriptingManager& scripting_manager = gEngine.GetScriptingManager();
	scripting_manager.LoadScript("farming_setup", "farming_setup.lua");
	scripting_manager.LoadScript("farming_update", "farming_update.lua");


	// Run game setup scripts.
	scripting_manager.RunScript("farming_setup");

	// All scripts added to the ECS will run every frame.
	ecs.Get<Script>(ecs.Create()).name = "farming_update";

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();
	

	std::cout << "Hello, World!\n";
	return 0;
}
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
#include "TileMapManager.h"

using namespace lilengine;

void UpdateCallback(Engine& e) {
	
}

int main(int argc, const char* argv[]) {
	gEngine.Startup();

	ECS& ecs = gEngine.GetECS();

	// Load up game scripts.
	ScriptingManager& scripting_manager = gEngine.GetScriptingManager();
	scripting_manager.LoadScript("pong_setup", "pong_setup.lua");
	scripting_manager.LoadScript("pong_update", "pong_update.lua");

	// Run game setup scripts.
	scripting_manager.RunScript("pong_setup");

	// All scripts added to the ECS will run every frame.
	ecs.Get<Script>(ecs.Create()).name = "pong_update";

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();
	
	return 0;
}
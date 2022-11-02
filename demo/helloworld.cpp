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

	// Load and run a game setup script.
	
	ScriptingManager& scripting_manager = gEngine.GetScriptingManager();
	scripting_manager.LoadScript("pong_setup", "pong_setup.lua");
	scripting_manager.RunScript("pong_setup");
	
	/*
	GraphicsManager& graphics_manager = gEngine.GetGraphicsManager();
	ECS& ecs = gEngine.GetECS();
	
	graphics_manager.LoadImage("spongebob", "spongebob.png");

	EntityID ball = ecs.Create();

	ecs.Get<Sprite>(ball).image_name = "spongebob";
	ecs.Get<Sprite>(ball).scale = vec3(100.0, 100.0, 0.0);
	ecs.Get<Sprite>(ball).rotation_axis = vec3(0, 0, 0);
	ecs.Get<Sprite>(ball).rotation_angle = 0.0;
	ecs.Get<Sprite>(ball).z = 1.0;

	ecs.Get<Position>(ball).x = 10.0;
	ecs.Get<Position>(ball).y = 0.0;
	*/

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();
	

	std::cout << "Hello, World!\n";
	return 0;
}
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
	/*
	TileMapManager& tile_map_manager = gEngine.GetTileMapManager();
	spdlog::info(tile_map_manager.GetTile(168, 90));
	*/
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

	// TILE MAP
	std::vector<string> tile_set{ "grass_1", "grass_2", "grass_3", "grass_4" };
	std::vector<int> world_map;
	for (int i = 0; i < 180; i++) {
		world_map.push_back(rand() % 4 + 1);
	}

	TileMapManager& tile_map_manager = gEngine.GetTileMapManager();
	tile_map_manager.LoadTileMap(tile_set, 10, world_map, 18, 10);

	gEngine.RunGameLoop(UpdateCallback);
	gEngine.Shutdown();

	std::cout << "Hello, World!\n";
	return 0;
}
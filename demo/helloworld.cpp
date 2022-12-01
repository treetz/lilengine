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
#include "NetworkManager.h"

using namespace lilengine;

void UpdateCallback(Engine& e) {

}

int main(int argc, const char* argv[]) {
	gEngine.Startup();

	//GraphicsManager& graphics_manager = gEngine.GetGraphicsManager();
	ECS& ecs = gEngine.GetECS();

	// Set up client
	//Client client;// create client entity
	// set up network manager instance
	// NetworkManager& networking_manager = gEngine.GetNetworkManager();
	// // set create client to Client struct 
	// networking_manager.client = networking_manager.CreateClient();
	// // assign client an id
	// client.id = ecs.Create();
	// // assign client data to Client struct
	// client.client = networking_manager.client;
	// printf("Your client id is %d\n", client.id);


	// Load up game scripts.
	ScriptingManager& scripting_manager = gEngine.GetScriptingManager();
	scripting_manager.LoadScript("pong_setup", "pong_setup.lua");
	scripting_manager.LoadScript("pong_update", "pong_update.lua");
	
	// Load up server scripts
	scripting_manager.LoadScript("client_tracker", "clients.lua");
	//scripting_manager.LoadScript("")

	// Run game setup scripts.
	scripting_manager.RunScript("pong_setup");

	// All scripts added to the ECS will run every frame.
	ecs.Get<Script>(ecs.Create()).name = "pong_update";

	/*
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

	// 
	// Client c;

	// NetworkManager& networking_manager = gEngine.GetNetworkManager();
	// networking_manager.CreateClient(networking_manager.client);
	// ecs.Get<c>(ecs.Create()).id = c.id;

	printf("Starting Game Loop!\n");
	gEngine.RunGameLoop(UpdateCallback);
	printf("Ending Game Loop!\n");
	gEngine.Shutdown();
	

	std::cout << "Hello, World!\n";
	return 0;
}
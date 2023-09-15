#pragma once

#include <thread>
#include <chrono>
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

namespace lilengine {

	// EngineImpl is the where the engine is implemented and stores its various managers
	class Engine::EngineImpl {
	public:
		GraphicsManager graphics_manager;
		InputManager input_manager;
		ResourceManager resource_manager;
		SoundManager sound_manager;
		ECS ecs;
		ScriptingManager scripting_manager;
		TileMapManager tile_map_manager;
	};

	// Constucter takes window dimensions or fullscreen option and instanciates the engine's implementation
	Engine::Engine(int window_width, int window_height, bool fullscreen) {
		impl_ = std::make_unique< EngineImpl >();
		impl_->graphics_manager = GraphicsManager(window_width, window_height, fullscreen);
	}

	Engine::~Engine() {}

	// Startup each component of the engine
	void Engine::Startup() {
		impl_->graphics_manager.Startup();
		impl_->input_manager.Startup();
		impl_->sound_manager.Startup();
		impl_->scripting_manager.Startup();
	}

	// Shutdown each component of the engine
	void Engine::Shutdown() {
		impl_->scripting_manager.Shutdown();
		impl_->sound_manager.Shutdown();
		impl_->input_manager.Shutdown();
		impl_->graphics_manager.Shutdown();
	}

	// Runs the engine's game loop
	void Engine::RunGameLoop(const UpdateCallback& callback) {
		
		// We must ensure the game loop runs 60 time per second
		// The code ran in the game loop should take less than 1/60 of a second so we must sleep for the rest of the time
		const auto one_sixtieth_of_a_second = std::chrono::duration<real>(1. / 60.);

		/* Timestep Testing 
		const auto t0 = std::chrono::steady_clock::now();
		spdlog::info("Starting Game Loop!");
		int tick_num = 1;
		*/

		while (true) {
			// Take the time at the start of the game loop
			const auto t1 = std::chrono::steady_clock::now();

			/* Timestep testing 
			if (std::chrono::duration<double>(t1 - t0).count() >= 1) {
				spdlog::info("Game Loop is Finished!");
				break;
			}	
			spdlog::info("Tick: {}", tick_num);
			tick_num++;
			*/

			// Call the Input Manager's update function to take in any keyboard inputs
			impl_->input_manager.Update();

			// If the user has clicked the 'X' on the window then break the game loop
			if (impl_->graphics_manager.ShouldQuit() == true) {
				break;
			}

			// Run loaded scripts
			impl_->scripting_manager.Update();

			// Call the inputted callback function
			callback(*this);

			// Draw loaded sprites to the screeen
			impl_->graphics_manager.Draw();

			// Manage timestep
			// Take time at the end loop iteration
			const auto t2 = std::chrono::steady_clock::now();

			// Get the ellapsed time and sleep the engine until this iteration reaches 1/60 of a second long
			std::chrono::duration<double> elapsed_time = t2 - t1;
			std::chrono::duration<double> wait_time = one_sixtieth_of_a_second - elapsed_time;
			std::this_thread::sleep_for(wait_time); 
		}
	}

	// Getter methods for each of the engine's components
	GraphicsManager& Engine::GetGraphicsManager() {
		return impl_->graphics_manager;
	}

	InputManager& Engine::GetInputManager() {
		return impl_->input_manager;
	}

	ResourceManager& Engine::GetResourceManager() {
		return impl_->resource_manager;
	}

	SoundManager& Engine::GetSoundManager() {
		return impl_->sound_manager;
	}

	ECS& Engine::GetECS() {
		return impl_->ecs;
	}

	ScriptingManager& Engine::GetScriptingManager() {
		return impl_->scripting_manager;
	}

	TileMapManager& Engine::GetTileMapManager() {
		return impl_->tile_map_manager;
	}
}
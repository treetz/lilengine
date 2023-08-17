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

	Engine::Engine(int window_width, int window_height, bool fullscreen) {
		impl_ = std::make_unique< EngineImpl >();
		impl_->graphics_manager = GraphicsManager(window_width, window_height, fullscreen);
	}

	Engine::~Engine() {}

	void Engine::Startup() {
		impl_->graphics_manager.Startup();
		impl_->input_manager.Startup();
		impl_->sound_manager.Startup();
		impl_->scripting_manager.Startup();
	}

	void Engine::Shutdown() {
		impl_->scripting_manager.Shutdown();
		impl_->sound_manager.Shutdown();
		impl_->input_manager.Shutdown();
		impl_->graphics_manager.Shutdown();
	}

	void Engine::RunGameLoop(const UpdateCallback& callback) {
		const auto one_sixtieth_of_a_second = std::chrono::duration<real>(1. / 60.);

		/* Timestep Testing 
		const auto t0 = std::chrono::steady_clock::now();
		spdlog::info("Starting Game Loop!");
		int tick_num = 1;
		*/

		while (true) {
			const auto t1 = std::chrono::steady_clock::now();

			/*// Timestep testing 
			if (std::chrono::duration<double>(t1 - t0).count() >= 1) {
				spdlog::info("Game Loop is Finished!");
				break;
			}	
			spdlog::info("Tick: {}", tick_num);
			tick_num++;
			*/

			impl_->input_manager.Update();

			if (impl_->graphics_manager.ShouldQuit() == true) {
				break;
			}

			// Run loaded scripts
			impl_->scripting_manager.Update();

			callback(*this);

			impl_->graphics_manager.Draw();

			// Manage timestep
			const auto t2 = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_time = t2 - t1;
			std::chrono::duration<double> wait_time = one_sixtieth_of_a_second - elapsed_time;
			std::this_thread::sleep_for(wait_time);
		}
	}

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
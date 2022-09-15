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

namespace lilengine {

	class Engine::EngineImpl {
	public:
		GraphicsManager graphics;
		InputManager input;
		ResourceManager resources;
		SoundManager sound;
	};

	Engine::Engine(int window_width, int window_height, bool fullscreen) {
		gEngine.impl_ = std::make_unique< EngineImpl >();
		gEngine.impl_->graphics = GraphicsManager(window_width, window_height, fullscreen);
	}

	Engine::~Engine() {

	}

	void Engine::Startup() {
		gEngine.impl_->graphics.Startup();
		gEngine.impl_->input.Startup();
		gEngine.impl_->sound.Startup();
	}

	void Engine::Shutdown() {
		gEngine.impl_->input.Shutdown();
		gEngine.impl_->graphics.Shutdown();
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

			/* Timestep testing 
			if (std::chrono::duration<double>(t1 - t0).count() >= 1) {
				spdlog::info("Game Loop is Finished!");
				break;
			}	
			spdlog::info("Tick: {}", tick_num);
			tick_num++;
			*/

			gEngine.impl_->input.Update();

			if (gEngine.impl_->graphics.ShouldQuit() == true) {
				break;
			}

			callback(*this);

			gEngine.impl_->graphics.Draw();

			// Manage timestep
			const auto t2 = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_time = t2 - t1;
			std::chrono::duration<double> wait_time = one_sixtieth_of_a_second - elapsed_time;
			std::this_thread::sleep_for(wait_time);
		}
	}

	GraphicsManager& Engine::GetGraphicsManager() {
		return impl_->graphics;
	}

	InputManager& Engine::GetInputManager() {
		return impl_->input;
	}

	ResourceManager& Engine::GetResourceManager() {
		return impl_->resources;
	}

	SoundManager& Engine::GetSoundManager() {
		return impl_->sound;
	}
}
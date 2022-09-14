#include <thread>
#include <chrono>
#include <iostream>

#include "spdlog/spdlog.h"

#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"

namespace lilengine {

	class Engine::EngineImpl {
	public:
		GraphicsManager graphics;
		InputManager input;
	};

	Engine::Engine(int window_width, int window_height, bool fullscreen) {
		impl_ = std::make_unique< EngineImpl >();

		/* Ask about error that occurs when initializing graphics with 
		 * pimpl implementaion for the GraphicsManager
		 */
		impl_->graphics = GraphicsManager(window_width, window_height, fullscreen);
		impl_->input = InputManager();
	}

	Engine::~Engine() {

	}

	void Engine::Startup() {
		impl_->graphics.Startup();
		impl_->input.Startup();
	}

	void Engine::Shutdown() {
		impl_->input.Shutdown();
		impl_->graphics.Shutdown();
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
			std::cout << "Tick: " << tick_num << "\n";
			tick++;
			*/

			impl_->input.Update();

			callback();

			//graphics.Draw();

			// Manage timestep
			const auto t2 = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_time = t2 - t1;
			std::chrono::duration<double> wait_time = one_sixtieth_of_a_second - elapsed_time;
			std::this_thread::sleep_for(wait_time);
		}
	}
}
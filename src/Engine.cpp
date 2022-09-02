#include <thread>
#include <chrono>

#include <iostream>

#include "Engine.h"

namespace lilengine {

	Engine::Engine(int window_width, int window_height, bool fullscreen) {
		graphics = GraphicsManager(window_width, window_height, fullscreen);
	}

	void Engine::Startup() {
		graphics.Startup();
		//input.Startup();
	}

	void Engine::Shutdown() {
		//input.Shutdown();
		graphics.Shutdown();
	}

	void Engine::RunGameLoop(/*UpdateCallack*/) {
		using namespace Types;

		const auto one_sixtieth_of_a_second = std::chrono::duration<real>(1. / 60.);

		//const auto start = std::chrono::steady_clock::now();

		int n = 1;

		while (true) {
			const auto t1 = std::chrono::steady_clock::now();

			/*
			std::chrono::duration<double> total_time = t1 - start;
			if (total_time.count() >= 1) {
				break;
			}
			
			std::cout << "You are in tick " << n << "\n";
			n += 1;
			*/

			//input.Update();

			//UpdateCallback();

			//graphics.Draw();

			// Manage timestep
			const auto t2 = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_time = t2 - t1;
			std::chrono::duration<double> wait_time = one_sixtieth_of_a_second - elapsed_time;
			std::this_thread::sleep_for(wait_time);
		}
	}
}
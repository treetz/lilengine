#pragma once

#include "Types.h"
#include "GraphicsManager.h"

namespace lilengine {

	class Engine {
	public:
		GraphicsManager graphics;
		//InputManager input;

		Engine(int window_width = 100, int window_height = 100, bool fullscreen = false);
		void Startup();
		void Shutdown();
		void RunGameLoop(/*UpdateCallback*/);
	};

	inline Engine gEngine;
}
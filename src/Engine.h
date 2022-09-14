#pragma once

#include <memory>

#include "Types.h"

namespace lilengine {
	using namespace Types;

	class Engine {
	public:
		Engine(int window_width = 100, int window_height = 100, 
			bool fullscreen = false);
		~Engine();

		void Startup();
		void Shutdown();
		void RunGameLoop(const UpdateCallback& callback);

	private:
		class EngineImpl;
		std::unique_ptr< EngineImpl > impl_;
	};

	inline Engine gEngine = Engine();
}
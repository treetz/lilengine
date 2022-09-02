#pragma once

#include "Types.h"

namespace lilengine {

	class GraphicsManager {
	public:
		GraphicsManager(int window_width = 100, int window_height = 100, bool window_fullscreen = false);
		void Startup();
		void Shutdown();
		void Draw();

	private:
		int window_width;
		int window_height;
		bool window_fullscreen;
	};
}
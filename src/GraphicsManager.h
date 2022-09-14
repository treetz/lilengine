#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

//#include <memory>

namespace lilengine {

	class GraphicsManager {
	friend class InputManager;

	public:
		GraphicsManager(int window_width = 100, int window_height = 100,
			bool window_fullscreen = false);
		~GraphicsManager();

		void Startup();
		void Shutdown();
		void Draw();

	private:
		int window_width;
		int window_height;
		bool window_fullscreen;
		GLFWwindow* window;
	};
}
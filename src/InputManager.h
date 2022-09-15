#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Engine.h"
#include "GraphicsManager.h"

namespace lilengine {

	class InputManager {
	public:
		InputManager();
		~InputManager();

		void Startup();
		void Shutdown();
		void Update();
		bool KeyIsPressed(int key);
	};
}
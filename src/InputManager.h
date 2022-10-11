#pragma once

#include "GLFW/glfw3.h"

#include "spdlog/spdlog.h"

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
		int GetKeyStatus(int key);
	};
}
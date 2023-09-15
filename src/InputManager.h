#pragma once

#include "GLFW/glfw3.h"

#include "spdlog/spdlog.h"

#include "Engine.h"
#include "GraphicsManager.h"

namespace lilengine {

	// The Input Manager class defines the manager in charge of collecting inputs from the user
	class InputManager {
	public:
		// Constructors
		InputManager();
		~InputManager();

		// Startup and Shutdown functions
		void Startup();
		void Shutdown();

		// Get inputs from user
		void Update();

		// Returns True if the inputted key is currently being pressed otherwise False
		bool KeyIsPressed(int key);

		// Returns the GLFW status of the inputted key
		int GetKeyStatus(int key);
	};
}
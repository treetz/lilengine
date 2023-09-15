#pragma once

#include "InputManager.h"

namespace lilengine {

	// Constructors
	InputManager::InputManager() {}
	InputManager::~InputManager() {}

	// Startup and Shutdown the Input Manager
	void InputManager::Startup() {}
	void InputManager::Shutdown() {}

	// Collects user inputs via GLFW
	void InputManager::Update() {
		glfwPollEvents();
	}

	// Returns True if the inputted key is currently being pressed otherwise False
	bool InputManager::KeyIsPressed(int GLFW_key) {
		if (glfwGetKey(gEngine.GetGraphicsManager().window, GLFW_key) == GLFW_PRESS) {
			return true;
		}
		else {
			return false;
		}
	}

	// Returns the GLFW status of the inputted key
	int InputManager::GetKeyStatus(int GLFW_key) {
		return glfwGetKey(gEngine.GetGraphicsManager().window, GLFW_key);
	}
}
#pragma once

#include <iostream>

#include "spdlog/spdlog.h"
#include "InputManager.h"

namespace lilengine {

	InputManager::InputManager() {

	}

	InputManager::~InputManager() {

	}

	void InputManager::Startup() {

	}

	void InputManager::Shutdown() {

	}

	void InputManager::Update() {
		glfwPollEvents();
	}

	bool InputManager::KeyIsPressed(int GLFW_key) {
		GLFWwindow* w = gEngine.GetGraphicsManager().window;
		if (glfwGetKey(w, GLFW_key) == GLFW_PRESS) {
			spdlog::info("Key {} was pressed!", GLFW_key);
			return true;
		}
		return false;
	}
}
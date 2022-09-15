#pragma once

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
		if (glfwGetKey(gEngine.GetGraphicsManager().window, GLFW_key) == GLFW_PRESS) {
			spdlog::info("Key {} was pressed!", GLFW_key);
			return true;
		}
		return false;
	}
}
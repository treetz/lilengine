#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "spdlog/spdlog.h"

#include "Engine.h"
#include "InputManager.h"
#include "GraphicsManager.h"

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
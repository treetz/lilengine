#pragma once

#include "spdlog/spdlog.h"

#include "Engine.h"
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

	bool InputManager::KeyIsPressed(int key) {
		/*
		if (glfwGetKey(gEngine.impl_->graphics.window, key) == GLFW_PRESS) {
			return true;
		}
		*/
		return false;
	}
}
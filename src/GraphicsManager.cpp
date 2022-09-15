#pragma once

#include "spdlog/spdlog.h"

#include "GraphicsManager.h"

namespace lilengine {

	GraphicsManager::GraphicsManager(int window_width, int window_height, bool window_fullscreen) {
		this->window_width = window_width;
		this->window_height = window_height;
		this->window_fullscreen = window_fullscreen;
	}

	GraphicsManager::~GraphicsManager() {

	}

	void GraphicsManager::Startup() {
		glfwInit();
		// We'll use sokol_gfx's OpenGL backend
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		this->window = glfwCreateWindow(window_width, window_height, "lilengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(this->window, window_width, window_height);
		if (!this->window)
		{

			spdlog::error("Failed to create a window.");
			glfwTerminate();
		}
		glfwMakeContextCurrent(this->window);
		glfwSwapInterval(1);
	}

	void GraphicsManager::Shutdown() {
		glfwTerminate();
	}

	void GraphicsManager::Draw() {

	}

	bool GraphicsManager::ShouldQuit() {
		if (glfwWindowShouldClose(this->window) == 1) {
			return true;
		}
		return false;
	}

	void GraphicsManager::SetShouldQuit() {
		glfwSetWindowShouldClose(this->window, true);
	}
}
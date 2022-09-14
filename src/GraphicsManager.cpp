#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "Types.h"
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

	/* pimpl Implementation
	class GraphicsManager::GraphicsManagerImpl {
	public:
		int window_width;
		int window_height;
		bool window_fullscreen;

		//std::unique_ptr< GlFWwindow > window;
	};

	GraphicsManager::GraphicsManager(int window_width, int window_height, bool window_fullscreen) {
		impl_ = std::make_unique< GraphicsManagerImpl >();
		impl_->window_width = window_width;
		impl_->window_height = window_height;
		impl_->window_fullscreen = window_fullscreen;
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
		GLFWwindow* window = glfwCreateWindow(impl_->window_width, impl_->window_height, "lilengine", impl_->window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(window, impl_->window_width, impl_->window_height);
		if (!window)
		{

			spdlog::error("Failed to create a window.");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
	}

	void GraphicsManager::Shutdown() {
		glfwTerminate();
	}

	void GraphicsManager::Draw() {

	}
	*/
}
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "GraphicsManager.h"

namespace lilengine {

	GraphicsManager::GraphicsManager(int window_width, int window_height, bool window_fullscreen) {
		this->window_width = window_width;
		this->window_height = window_height;
		this->window_fullscreen = window_fullscreen;
	}

	void GraphicsManager::Startup() {
		glfwInit();
		// We'll use sokol_gfx's OpenGL backend
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(window_width, window_height, "lilengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(window, window_width, window_height);
		if (!window)
		{
			/*std::cerr << "Failed to create a window." << std::endl;*/
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
}
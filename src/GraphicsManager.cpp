#pragma once

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#include "GraphicsManager.h"

#include "spdlog/spdlog.h"

namespace lilengine {

	GraphicsManager::GraphicsManager(int window_width, int window_height, bool window_fullscreen) {
		this->window_width = window_width;
		this->window_height = window_height;
		this->window_fullscreen = window_fullscreen;
	}

	GraphicsManager::~GraphicsManager() {

	}

	void GraphicsManager::Startup() {
		// Window Setup
		glfwInit();
		// We'll use sokol_gfx's OpenGL backend
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(window_width, window_height, "lilengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(window, window_width, window_height);
		if (!window)
		{

			spdlog::error("Failed to create a window.");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		// Image Drawing Setup
		sg_setup(sg_desc{});

		// A vertex buffer containing a textured square.
		const float vertices[] = {
			// positions      // texcoords
			-1.0f,  -1.0f,    0.0f,  0.0f,
			 1.0f,  -1.0f,    1.0f,  0.0f,
			-1.0f,   1.0f,    0.0f,  1.0f,
			 1.0f,   1.0f,    1.0f,  1.0f,
		};

		sg_buffer_desc buffer_desc{};
		buffer_desc.data = SG_RANGE(vertices);

		sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);

		sg_pipeline_desc pipeline_desc{};

		pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
		
		// Alpha Blending
		pipeline_desc.colors[0].blend.enabled = true;
		pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
		pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
	}

	void GraphicsManager::Shutdown() {
		sg_shutdown();
		glfwTerminate();
	}

	void GraphicsManager::Draw() {

	}

	bool GraphicsManager::ShouldQuit() {
		if (glfwWindowShouldClose(window) == 1) {
			return true;
		}
		return false;
	}

	void GraphicsManager::SetShouldQuit() {
		glfwSetWindowShouldClose(window, true);
	}
}
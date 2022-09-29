#pragma once

#include <unordered_map>
#include <algorithm>

#include "GLFW/glfw3.h"
#include "sokol_gfx.h"
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "spdlog/spdlog.h"

#include "Types.h"
#include "Engine.h"
#include "ResourceManager.h"

namespace lilengine {
	using namespace Types;

	struct Image {
		sg_image image;
		int width, height;
	};

	struct Sprite {
		string image_name;
		vec2 position;
		vec3 scale, rotation_axis;
		float rotation_angle, z;
	};

	class GraphicsManager {
	friend class InputManager;
	public:
		GraphicsManager(int window_width = 100, int window_height = 100,
			bool window_fullscreen = false);
		~GraphicsManager();

		void Startup();
		void Shutdown();
		void Draw(const std::vector< Sprite >& sprites);
		bool ShouldQuit();
		void SetShouldQuit();
		bool LoadImage(const string& name, const string& p);
		bool DestroyImage(const string& name);

	private:
		int window_width, window_height;
		bool window_fullscreen;
		GLFWwindow* window;
		std::unordered_map< string, Image > name_to_image_map;
		sg_pipeline pipeline;
		sg_pass_action pass_action{};
		sg_bindings bindings{};
	};
}
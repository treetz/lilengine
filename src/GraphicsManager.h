#pragma once

#include <unordered_map>
#include <algorithm>

#include "GLFW/glfw3.h"
//#include "sokol_gfx.h" -- Included in Types.h
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "spdlog/spdlog.h"

#include "Types.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "ECS.h"

namespace lilengine {
	using namespace Types;

	// The Graphics Manager class is in charge of loading, destroying, and displaying images
	class GraphicsManager {
	friend class InputManager; // Allows the Input Manager to access the Graphics Manager's GLFW window so it can get user inputs
	public:
		// Constructors/Destructors
		GraphicsManager(int window_width = 100, int window_height = 100, bool window_fullscreen = false); // Creates a small window by default
		~GraphicsManager();

		// Startup and Shutdown functions
		void Startup();
		void Shutdown();

		// Draw loaded images to the window
		void Draw();

		// Returns True if the 'X' button had been clicked on the window
		bool ShouldQuit();

		// Sets the GLFW window to close
		void SetShouldQuit();

		// Loads an image into the name_to_image_map
		bool LoadImage(const string& name, const string& p);

		// Removes an image from the name_to_image_map
		bool DestroyImage(const string& name);
		
		// Getters for window and image dimensions
		int GetWindowWidth();
		int GetWindowHeight();
		int GetImageWidth(const string& name);
		int GetImageHeight(const string& name);

	private:
		int window_width, window_height; // Window dimensions
		bool window_fullscreen; // True if window should be fullscreen
		GLFWwindow* window;
		std::unordered_map< string, Image > name_to_image_map; // Maps an image name to its SG Image
		sg_pipeline pipeline;
		sg_pass_action pass_action{};
		sg_bindings bindings{};
	};
}
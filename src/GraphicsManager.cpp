#pragma once

// Window API
#define GLFW_INCLUDE_NONE

// Graphics Pipeline API
#define SOKOL_IMPL
#define SOKOL_GLCORE33

// Image Loader API
#define STB_IMAGE_IMPLEMENTATION

#include "GraphicsManager.h"

#include <iostream>

using namespace glm;

// The Uniforms struct will not be used outside the graphics manager so it can be defined within an anonymous namespace
namespace {

	// The Uniforms structs are 4x4 matricies used within the vertex shader
	struct Uniforms {
		mat4 projection;
		mat4 transform;
	};
}

namespace lilengine {

	// Constructor sets the window dimensions 
	GraphicsManager::GraphicsManager(int window_width, int window_height, bool window_fullscreen) {
		this->window_width = window_width;
		this->window_height = window_height;
		this->window_fullscreen = window_fullscreen;
	}
	GraphicsManager::~GraphicsManager() {}

	// Startup function sets up the GLFW window and the graphics pipeline
	void GraphicsManager::Startup() {
	// **********************************************************************************************************************************************************
	// PROVIDED BY PROFESSOR
	
	// Setup the window:
		glfwInit(); // Initialize the window
		// We'll use sokol_gfx's OpenGL backend
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(window_width, window_height, "lilengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(window, window_width, window_height);
		if (!window) {
			spdlog::error("Failed to create a window.");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

	// Setup the graphics pipeline:
		sg_setup(sg_desc{}); // Initialize sokol_gfx

	// Describe the data our pipeline will be using:
		// A vertex buffer containing a textured square.
		const float vertices[] = {
			// positions      // texcoords
			-1.0f,  -1.0f,    0.0f,  0.0f,
			 1.0f,  -1.0f,    1.0f,  0.0f,
			-1.0f,   1.0f,    0.0f,  1.0f,
			 1.0f,   1.0f,    1.0f,  1.0f,
		};

		// Copy this data to the GPU memory
		sg_buffer_desc buffer_desc{};
		buffer_desc.data = SG_RANGE(vertices); 
		sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);

	// Define the pipeline's discription:
		// Tell the pipeline what our data represents
		sg_pipeline_desc pipeline_desc{};
		pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
		
		// Enable alpha blending
		pipeline_desc.colors[0].blend.enabled = true;
		pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
		pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
		
		// Enable the depth-buffer (aka z-buffer)
		pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
		pipeline_desc.depth.write_enabled = true;

		// Tell the pipeline about our vertex data layout
		pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
		pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

	// Define the shader's description:
		sg_shader_desc shader_desc{};

		// Define a simple vertex shader   
		shader_desc.vs.source = R"(
			#version 330
			uniform mat4 projection;
			uniform mat4 transform;
			layout(location=0) in vec2 position;
			layout(location=1) in vec2 texcoords0;
			out vec2 texcoords;
			void main() {
				gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
				texcoords = texcoords0;
			})";

		// Tell the shader about the Uniforms struct
		shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
		// The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
		shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
		shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
		shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
		shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

	// Define the fragment shader
		shader_desc.fs.source = R"(
			#version 330
			uniform sampler2D tex;
			in vec2 texcoords;
			out vec4 frag_color;
			void main() {
				frag_color = texture( tex, texcoords );
				// If we're not drawing back to front, discard very transparent pixels so we
				// don't write to the depth buffer and prevent farther sprites from drawing.
				if( frag_color.a < 0.1 ) discard;
			}
		)";
		shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
		shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

		// Add the fragment shader to the pipeline
		pipeline_desc.shader = sg_make_shader(shader_desc);
		pipeline = sg_make_pipeline(pipeline_desc);

	// Define the pass action 
		// Clear the contents of sokol_gfx's frame buffer
		pass_action.colors[0].action = SG_ACTION_CLEAR;
		pass_action.colors[0].value = { 0.f, 0.f, 0.f, 0.f/* red, green, blue, alpha floating point values for a color to fill the frame buffer with */ };

	// Define the bindings
		// Bind our vertex buffer data to our pipeline
		bindings.vertex_buffers[0] = vertex_buffer;

	// **********************************************************************************************************************************************************
	}

	// Shuts down the graphics pipeline and closes the window
	void GraphicsManager::Shutdown() {
		sg_shutdown(); // Shutdown sokol_gfx
		glfwTerminate(); // Close the window
	}

	// Draw loaded images to the window
	void GraphicsManager::Draw() {
	// **********************************************************************************************************************************************************
	// PROVIDED BY PROFESSOR

	// Get the current frame buffer size
		glfwGetFramebufferSize(window, &window_width, &window_height);

	// Clear the default frame buffer
		sg_begin_default_pass(pass_action, window_width, window_height);

	// Create an instance of Uniforms 
		Uniforms uniforms;

	// Fill out the uniform's projection field:
		// Start with an identity matrix.
		uniforms.projection = mat4{ 1 };
		// Scale x and y by 1/100.
		uniforms.projection[0][0] = uniforms.projection[1][1] = 1.f / 100.f;
		// Scale the long edge by an additional 1/(long/short) = short/long.
		if (window_width < window_height) {
			uniforms.projection[1][1] *= window_width;
			uniforms.projection[1][1] /= window_height;
		}
		else {
			uniforms.projection[0][0] *= window_height;
			uniforms.projection[0][0] /= window_width;
		}

	// Apply the pipeline
		sg_apply_pipeline(pipeline);

	// **********************************************************************************************************************************************************

	// Draw each sprite:
		ECS& ecs = gEngine.GetECS();

		ecs.ForEach<Sprite>( [&]( EntityID e ) {

			Sprite& sprite = ecs.Get<Sprite>(e);
			Position& position = ecs.Get<Position>(e);

			if (name_to_image_map.count(sprite.image_name) == 0) {
				spdlog::error("Sprite name {} not found in name_to_image_map", sprite.image_name);
			}

			// Get the sprite's loaded image
			Image image = name_to_image_map[sprite.image_name];

	// **********************************************************************************************************************************************************
	// PROVIDED BY PROFESSOR
	
			// Fill out the uniform's transform field:
				// Figure out where to add rotate function:
				//		rotate(mat4{}, radians(sprite.rotation_angle), sprite.rotation_axis)
			uniforms.transform = translate(mat4{ 1 }, vec3(position.x, position.y, sprite.z)) * scale(mat4{ 1 }, vec3(sprite.scale));

			// Scale down the quad so the image always fits within the square
			if (image.width < image.height) {
				uniforms.transform = uniforms.transform * scale(mat4{ 1 }, vec3(real(image.width) / image.height, -1.0, 1.0));
			}
			else {
				uniforms.transform = uniforms.transform * scale(mat4{ 1 }, vec3(1.0, -real(image.height) / image.width, 1.0));
			}

			sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));

			// Bind the sprite's image to the fragment shader
			bindings.fs_images[0] = image.image;
			sg_apply_bindings(bindings);

			// Draw one instance of our quad
			sg_draw(0, 4, 1);
		} );

	// Finish drawing
		sg_end_pass();
		sg_commit();
		glfwSwapBuffers(window);

	// **********************************************************************************************************************************************************
	}

	// Returns True if the 'X' button had been clicked on the window
	bool GraphicsManager::ShouldQuit() {
		if (glfwWindowShouldClose(window) == 1) {
			return true;
		}
		return false;
	}

	// Sets the GLFW window to close
	void GraphicsManager::SetShouldQuit() {
		glfwSetWindowShouldClose(window, true);
	}

	// Loads an image into the name_to_image_map
	bool GraphicsManager::LoadImage(const string& name, const string& p) {
		spdlog::info("Loading Image: {}", p); // Inform the user that their image is being loaded
		
		// Only load images that haven't already been loaded
		if (name_to_image_map.count(name) == 0) {

			// Set the Resource Manager's root path to the sprites subdirectory and resolve the path to the image 
			gEngine.GetResourceManager().SetRootPath("assets//sprites");
			path resolved_path = gEngine.GetResourceManager().ResolvePath(p);

	// **********************************************************************************************************************************************************
	// PROVIDED BY PROFESSOR

			// Load the image and save its dimensions and channels
			int width, height, channels;
			unsigned char* data = stbi_load(resolved_path.string().c_str(), &width, &height, &channels, 4);

			// Create a sokol_gfx image description with the data returned from loading the image
			sg_image_desc image_desc{};
			image_desc.width = width;
			image_desc.height = height;
			image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
			image_desc.min_filter = SG_FILTER_LINEAR;
			image_desc.mag_filter = SG_FILTER_LINEAR;
			image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
			image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
			image_desc.data.subimage[0][0].ptr = data;
			image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);

			// Upload the image to the GPU
			sg_image image = sg_make_image(image_desc);

	// **********************************************************************************************************************************************************

			// Create an Image struct and add it to the name
			Image i;
			i.image = image;
			i.width = width;
			i.height = height;

			name_to_image_map[name] = i;

			// Once the GPU has the image data we can free its memory
			stbi_image_free(data);
		}
		return true;
	}

	// Removes an image from the name_to_image_map
	bool GraphicsManager::DestroyImage(const string& name) {
		// If the image has been loaded previously then remove it
		if (name_to_image_map.count(name) != 0) {
			name_to_image_map.erase(name);
			return true;
		}
		// Otherwise log an error
		else {
			spdlog::error("The {} image has not been loaded yet.", name);
			return false;
		}
	}

	// Returns the width of the GLFW window
	int GraphicsManager::GetWindowWidth() {
		return window_width;
	}

	// Returns the height of the GLFW window
	int GraphicsManager::GetWindowHeight() {
		return window_height;
	}

	// Returns the width of a loaded image
	int GraphicsManager::GetImageWidth(const string& name) {
		// If the image has been loaded then return the width
		if (name_to_image_map.count(name) != 0) {
			return name_to_image_map[name].width;
		}
		// Otherwise log an error
		else {
			spdlog::error("The {} image has not been loaded yet.", name);
			return -1;
		}
	}

	// Returns the height of a loaded image
	int GraphicsManager::GetImageHeight(const string& name) {
		// If the image has been loaded then return the height
		if (name_to_image_map.count(name) != 0) {
			return name_to_image_map[name].height;
		}
		// Otherwise log an error
		else {
			spdlog::error("The {} image has not been loaded yet.", name);
			return -1;
		}
	}
}
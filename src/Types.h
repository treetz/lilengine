#pragma once

#include <string>

#include "sokol_gfx.h"
#include "glm/glm.hpp"

// The Types namespace declares common types used throughout the engine
namespace Types {
	typedef double real;
	typedef std::string string;
	typedef glm::vec2 vec2;
	typedef glm::vec3 vec3;
	typedef glm::vec4 vec4;

	// Game Object Components
	struct Position { real x, y; };
	struct Velocity { real x, y; };
	struct Gravity { real meters_per_second; };
	struct Image { sg_image image; int width, height; };
	struct Sprite { string image_name; vec3 scale, rotation_axis; float rotation_angle, z; };
	struct Health { real percent; };
	struct Script { string name; };
}
#pragma once

#include <string>

#include "sokol_gfx.h"
#include "glm/glm.hpp"

namespace Types {
	typedef double real;
	typedef std::string string;
	typedef glm::vec2 vec2;
	typedef glm::vec3 vec3;
	typedef glm::vec4 vec4;

	// Game Object Components
	struct Position : public vec2 {};
	struct Velocity : public vec2 {};
	struct Gravity { real meters_per_second; };
	struct Image { sg_image image; int width, height; };
	struct Sprite { string image_name; vec2 position; vec3 scale, rotation_axis; float rotation_angle, z; };
	struct Health { real percent; };
	struct Script { string name; };
}
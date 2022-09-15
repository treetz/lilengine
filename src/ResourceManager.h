#pragma once

#include <filesystem>

namespace lilengine {

	typedef std::filesystem::path path;

	class ResourceManager {
	public:
		path ResolvePath(path p);
	};
}
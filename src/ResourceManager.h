#pragma once

#include <fstream>
#include <filesystem>

namespace lilengine {

	typedef std::filesystem::path path;

	class ResourceManager {
	public:
		path root = "assets";

		path ResolvePath(path p);
		void SetRootPath(path p);
	};
}
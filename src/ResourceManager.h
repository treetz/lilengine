#pragma once

#include <fstream>
#include <filesystem>

namespace lilengine {

	typedef std::filesystem::path path;

	// The Resource Manager class is in charge of resolving paths to resources within the assets folder 
	class ResourceManager {
	public:
		// The default path root is the assets folder
		path root = "assets";

		// Resolves the inputted "file name" (path) to an asset within the assets subdirectories
		path ResolvePath(path p);

		// Sets the root path of the Resource Manager
		void SetRootPath(path p);
	};
}
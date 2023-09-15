#pragma once

#include "ResourceManager.h"

namespace lilengine {
	
	// // Resolves the inputted "file name" (path) to an asset within the assets subdirectories
	path ResourceManager::ResolvePath(path p) {		
		return root / p;
	}

	// Sets the root path of the Resource Manager
	void ResourceManager::SetRootPath(path p) {
		root = p;
	}
}
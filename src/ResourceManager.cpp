#pragma once

#include "ResourceManager.h"

namespace lilengine {
	
	path ResourceManager::ResolvePath(path p) {		
		return root / p;
	}

	void ResourceManager::SetRootPath(path p) {
		root = p;
	}
}
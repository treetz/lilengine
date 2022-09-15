#pragma once

#include "ResourceManager.h"

namespace lilengine {
	
	path ResourceManager::ResolvePath(path p) {
		/*
		const path relative_to_assets = path("assets") / p;
		return relative_to_assets;
		*/
		
		const path root{ "assets" };
		return root / p;
		
	}
}
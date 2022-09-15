#pragma once

#include "ResourceManager.h"

namespace lilengine {
	
	path ResourceManager::ResolvePath(path p) {
		const path root{ "assets" };
		return root / p;
	}
}
#pragma once

#include "SoundManager.h"

#include "spdlog/spdlog.h"

namespace lilengine {

	SoundManager::SoundManager() {}

	SoundManager::~SoundManager() {}

	void SoundManager::Startup() {
		gSoloud.init();
	}

	void SoundManager::Shutdown() {
		gSoloud.deinit();
	}

	bool SoundManager::LoadSound(const string& name, const string& p) {
		spdlog::info("Loading sound: {}", p);
		
		// If the sound has not been loaded into the engine yet load it.
		if (name_to_sound_map.count(name) == 0) {
			gEngine.GetResourceManager().SetRootPath("assets//sounds");
			path resolved_path = gEngine.GetResourceManager().ResolvePath(p);
			name_to_sound_map[name].load(resolved_path.string().c_str());
		}

		spdlog::info("Sound loaded.");
		return true;
	}

	bool SoundManager::DestroySound(const string& name) {
		if (name_to_sound_map.count(name) != 0) {
			name_to_sound_map.erase(name);
			return true;
		}
		else {
			spdlog::error("The {} sound has not been loaded yet.", name);
			return false;
		}
	}

	bool SoundManager::PlaySound(const string& name) {
		// If the sound has been loaded into the engine then play it
		if (name_to_sound_map.count(name) != 0) {
			gSoloud.play(name_to_sound_map[name]);
			return true;
		}
		// Else print an error and return false
		else {
			spdlog::error("The {} sound has not been loaded yet.", name);
			return false;
		}
	}
}
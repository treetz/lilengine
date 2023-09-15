#pragma once

#include "SoundManager.h"

#include "spdlog/spdlog.h"

namespace lilengine {

	// Constructors
	SoundManager::SoundManager() {}
	SoundManager::~SoundManager() {}

	// Startup the Sound Manager
	void SoundManager::Startup() {
		// Initialize the global instance of SoLoud
		gSoloud.init();
	}

	// Shutdown the Sound Manager
	void SoundManager::Shutdown() {
		// Deinitialize the global instance of SoLoud
		gSoloud.deinit();
	}

	// Loads sounds into the name_to_sound_map
	bool SoundManager::LoadSound(const string& name, const string& p) {
		spdlog::info("Loading sound: {}", p); // Provide logging so the user knows assets are being loaded
		
		// If the sound has not been loaded into the engine yet load it.
		if (name_to_sound_map.count(name) == 0) {
			// Set the root path of the resource manager to the sounds subdirectory of the assets folder and resolve the path
			gEngine.GetResourceManager().SetRootPath("assets//sounds"); 
			path resolved_path = gEngine.GetResourceManager().ResolvePath(p);

			// Map the inputted name to a SoLoud Wav loaded from 'assets/sounds'
			name_to_sound_map[name].load(resolved_path.string().c_str());
		}
		return true;
	}

	// Removes sounds from the name_to_sound_map
	bool SoundManager::DestroySound(const string& name) {
		// If the sound is found in the name_to_sound_map then remove it
		if (name_to_sound_map.count(name) != 0) {
			name_to_sound_map.erase(name);
			return true;
		}
		// Otherwise log an error
		else {
			spdlog::error("The {} sound has not been loaded yet.", name);
			return false;
		}
	}

	// Plays sounds loaded into the engine
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
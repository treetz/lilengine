#pragma once

#include <iostream>
#include "SoundManager.h"

namespace lilengine {

	SoundManager::SoundManager() {

	}

	SoundManager::~SoundManager() {

	}

	void SoundManager::Startup() {
		soloud.init();
	}

	void SoundManager::Shutdown() {
		soloud.deinit();
	}

	bool SoundManager::LoadSound(const string& name, const string& p) {
		std::cout << "Hello from LoadSound()\nLoading: " << name << "\n";

		//if (name_to_sound_map.count(name) != 0) {
			path resolved_path = gEngine.GetResourceManager().ResolvePath(p);

			std::cout << "resolved path: " << resolved_path;

			//SoLoud::Wav sample;    // One sample

			//sample.load(resolved_path.string().c_str()); // Load a wave file
			//soloud.play(sample);        // Play it

			/* Ask about error that causes the executable to crash. I 
			 * believe it has to due with SoLoud::Wav showing up as an
			 * error-type. Error occurs when 
			 */
			name_to_sound_map[name].load(resolved_path.string().c_str());

		//}
		return true;
	}

	bool SoundManager::DestroySound(const string& name) {
		name_to_sound_map.erase(name);
		return true;
	}

	bool SoundManager::PlaySound(const string& name) {
		soloud.play(name_to_sound_map[name]);
		return true;
	}
}
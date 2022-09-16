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

		path resolved_path = gEngine.GetResourceManager().ResolvePath(p);

		sample.load(resolved_path.string().c_str());

		std::cout << "Life is great!" << "\n";
		//name_to_sound_map[name] = sample;
		
		//if (name_to_sound_map.count(name) != 0) {

			/* Ask about error */

			//name_to_sound_map[name].load(resolved_path.string().c_str());

		//}
		return true;
	}

	bool SoundManager::DestroySound(const string& name) {
		name_to_sound_map.erase(name);
		return true;
	}

	bool SoundManager::PlaySound(const string& name) {
		soloud.play(sample);//name_to_sound_map[name]);
		return true;
	}
}
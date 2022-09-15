#pragma once

#include "SoundManager.h"

namespace lilengine {

	SoundManager::SoundManager() {

	}

	SoundManager::~SoundManager() {

	}

	void SoundManager::Startup() {
		this->sl.init();
	}

	void SoundManager::Shutdown() {
		this->sl.deinit();
	}

	bool SoundManager::LoadSound(const string& name, const string& p) {
		path resolved_path = gEngine.GetResourceManager().ResolvePath(p);

		/* Ask about error */
		this->name_to_sound_map[name].load(resolved_path.c_str());

		return true;
	}

	bool SoundManager::DestroySound(const string& name) {
		this->name_to_sound_map.erase(name);
		return true;
	}

	bool SoundManager::PlaySound(const string& name) {
		this->sl.play(name_to_sound_map[name]);
		return true;
	}
}
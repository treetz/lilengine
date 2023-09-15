#pragma once

#include <unordered_map>

#include "soloud.h"
#include "soloud_wav.h"

#include "spdlog/spdlog.h"

#include "Types.h"
#include "Engine.h"
#include "ResourceManager.h"

namespace lilengine {
	using namespace Types;

	// The Sound Manager class is in charge of loading, removing, and playing sounds
	class SoundManager {
	public:
		SoundManager();
		~SoundManager();

		// Startup and Shutdown functions
		void Startup();
		void Shutdown();

		// Loads sounds into the name_to_sound_map
		bool LoadSound(const string& name, const string& path);

		// Removes sounds from the name_to_sound_map
		bool DestroySound(const string& name);

		// Plays sounds loaded into the engine
		bool PlaySound(const string& name);

	private:
		SoLoud::Soloud gSoloud; // Global SoLoud instance
		std::unordered_map< string, SoLoud::Wav > name_to_sound_map; // Maps sound name to their SoLoud Wav object
	};
}
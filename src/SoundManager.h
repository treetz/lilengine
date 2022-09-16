#pragma once

#include <unordered_map>

#include "Types.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "soloud.h"
#include "soloud_wav.h"

namespace lilengine {
	using namespace Types;

	class SoundManager {
	public:
		SoLoud::Soloud soloud;
		std::unordered_map< string, SoLoud::Wav > name_to_sound_map;

		SoLoud::Wav sample;

		SoundManager();
		~SoundManager();

		void Startup();
		void Shutdown();
		bool LoadSound(const string& name, const string& path);
		bool DestroySound(const string& name);
		bool PlaySound(const string& name);
	};
}
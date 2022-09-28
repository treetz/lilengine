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

	class SoundManager {
	public:
		SoundManager();
		~SoundManager();

		void Startup();
		void Shutdown();
		bool LoadSound(const string& name, const string& path);
		bool DestroySound(const string& name);
		bool PlaySound(const string& name);

	private:
		SoLoud::Soloud gSoloud;
		std::unordered_map< string, SoLoud::Wav > name_to_sound_map;
	};
}
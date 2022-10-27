#pragma once

#include <unordered_map>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "Types.h"
#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"

namespace lilengine {
	using namespace Types;

	class ScriptingManager {
	public:
		ScriptingManager();
		~ScriptingManager();

		void Startup();
		void Shutdown();
		void Update();
		bool LoadScript(const string& name, const string& path);
		bool RunScript(const string& name);

	private:
		sol::state lua;
		std::unordered_map< string, sol::load_result > name_to_script_map;
	};
}
#pragma once

#include <unordered_map>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "spdlog/spdlog.h"
#include <math.h>

#include "Types.h"
#include "Engine.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ECS.h"
#include "TileMapManager.h"

namespace lilengine {
	using namespace Types;

	// The Scripting Manager class is in charge of loading and running Lua scripts written by users
	class ScriptingManager {
	public:
		// Constructor/Destructor
		ScriptingManager();
		~ScriptingManager();

		// Startup and Shutdown functions
		void Startup();
		void Shutdown();

		// Runs each of the scripts loaded into the Entity Component System
		void Update();

		// Loads a script into the name_to_script_map
		bool LoadScript(const string& name, const string& path);

		// Runs a loaded script
		bool RunScript(const string& name);

	private:
		sol::state lua;
		std::unordered_map< string, sol::load_result > name_to_script_map;
	};
}
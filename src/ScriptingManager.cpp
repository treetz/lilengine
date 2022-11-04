#pragma once

#include "ScriptingManager.h"

namespace lilengine {

	ScriptingManager::ScriptingManager() {}
	ScriptingManager::~ScriptingManager() {}

	void ScriptingManager::Startup() {

		lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
		
		// Make the math random seed always the same for debugging.
		//lua.script("math.randomseed(0)");

		// Expose the input managers functionality to Lua.
		lua.set_function("KeyIsDown", 
			[&](const int keycode) { 
				return gEngine.GetInputManager().KeyIsPressed(keycode); 
			} 
		);

		// Create a Lua enum for the keyboard keys. This will allow
		// Lua scripts to call:
		//     KeyIsDown( KEYBOARD.SPACE )
		lua.new_enum("KEYBOARD",
			"SPACE", GLFW_KEY_SPACE,
			"APOSTROPHE", GLFW_KEY_APOSTROPHE,
			"COMMA", GLFW_KEY_COMMA,
			"MINUS", GLFW_KEY_MINUS,
			"PERIOD", GLFW_KEY_PERIOD,
			"SLASH", GLFW_KEY_SLASH,
			"0", GLFW_KEY_0,
			"1", GLFW_KEY_1,
			"2", GLFW_KEY_2,
			"3", GLFW_KEY_3,
			"4", GLFW_KEY_4,
			"5", GLFW_KEY_5,
			"6", GLFW_KEY_6,
			"7", GLFW_KEY_7,
			"8", GLFW_KEY_8,
			"9", GLFW_KEY_9,
			"SEMICOLON", GLFW_KEY_SEMICOLON,
			"EQUAL", GLFW_KEY_EQUAL,
			"A", GLFW_KEY_A,
			"B", GLFW_KEY_B,
			"C", GLFW_KEY_C,
			"D", GLFW_KEY_D,
			"E", GLFW_KEY_E,
			"F", GLFW_KEY_F,
			"G", GLFW_KEY_G,
			"H", GLFW_KEY_H,
			"I", GLFW_KEY_I,
			"J", GLFW_KEY_J,
			"K", GLFW_KEY_K,
			"L", GLFW_KEY_L,
			"M", GLFW_KEY_M,
			"N", GLFW_KEY_N,
			"O", GLFW_KEY_O,
			"P", GLFW_KEY_P,
			"Q", GLFW_KEY_Q,
			"R", GLFW_KEY_R,
			"S", GLFW_KEY_S,
			"T", GLFW_KEY_T,
			"U", GLFW_KEY_U,
			"V", GLFW_KEY_V,
			"W", GLFW_KEY_W,
			"X", GLFW_KEY_X,
			"Y", GLFW_KEY_Y,
			"Z", GLFW_KEY_Z,
			"LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET,
			"BACKSLASH", GLFW_KEY_BACKSLASH,
			"RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET,
			"GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT,
			"WORLD_1", GLFW_KEY_WORLD_1,
			"WORLD_2", GLFW_KEY_WORLD_2,
			"ESCAPE", GLFW_KEY_ESCAPE,
			"ENTER", GLFW_KEY_ENTER,
			"TAB", GLFW_KEY_TAB,
			"BACKSPACE", GLFW_KEY_BACKSPACE,
			"INSERT", GLFW_KEY_INSERT,
			"DELETE", GLFW_KEY_DELETE,
			"RIGHT", GLFW_KEY_RIGHT,
			"LEFT", GLFW_KEY_LEFT,
			"DOWN", GLFW_KEY_DOWN,
			"UP", GLFW_KEY_UP,
			"PAGE_UP", GLFW_KEY_PAGE_UP,
			"PAGE_DOWN", GLFW_KEY_PAGE_DOWN,
			"HOME", GLFW_KEY_HOME,
			"END", GLFW_KEY_END,
			"CAPS_LOCK", GLFW_KEY_CAPS_LOCK,
			"SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK,
			"NUM_LOCK", GLFW_KEY_NUM_LOCK,
			"PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN,
			"PAUSE", GLFW_KEY_PAUSE,
			"F1", GLFW_KEY_F1,
			"F2", GLFW_KEY_F2,
			"F3", GLFW_KEY_F3,
			"F4", GLFW_KEY_F4,
			"F5", GLFW_KEY_F5,
			"F6", GLFW_KEY_F6,
			"F7", GLFW_KEY_F7,
			"F8", GLFW_KEY_F8,
			"F9", GLFW_KEY_F9,
			"F10", GLFW_KEY_F10,
			"F11", GLFW_KEY_F11,
			"F12", GLFW_KEY_F12,
			"F13", GLFW_KEY_F13,
			"F14", GLFW_KEY_F14,
			"F15", GLFW_KEY_F15,
			"F16", GLFW_KEY_F16,
			"F17", GLFW_KEY_F17,
			"F18", GLFW_KEY_F18,
			"F19", GLFW_KEY_F19,
			"F20", GLFW_KEY_F20,
			"KP_0", GLFW_KEY_KP_0,
			"KP_1", GLFW_KEY_KP_1,
			"KP_2", GLFW_KEY_KP_2,
			"KP_3", GLFW_KEY_KP_3,
			"KP_4", GLFW_KEY_KP_4,
			"KP_5", GLFW_KEY_KP_5,
			"KP_6", GLFW_KEY_KP_6,
			"KP_7", GLFW_KEY_KP_7,
			"KP_8", GLFW_KEY_KP_8,
			"KP_9", GLFW_KEY_KP_9,
			"KP_DECIMAL", GLFW_KEY_KP_DECIMAL,
			"KP_DIVIDE", GLFW_KEY_KP_DIVIDE,
			"KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY,
			"KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT,
			"KP_ADD", GLFW_KEY_KP_ADD,
			"KP_ENTER", GLFW_KEY_KP_ENTER,
			"KP_EQUAL", GLFW_KEY_KP_EQUAL,
			"LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT,
			"LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL,
			"LEFT_ALT", GLFW_KEY_LEFT_ALT,
			"LEFT_SUPER", GLFW_KEY_LEFT_SUPER,
			"RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT,
			"RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL,
			"RIGHT_ALT", GLFW_KEY_RIGHT_ALT,
			"RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER,
			"MENU", GLFW_KEY_MENU,
			"LAST", GLFW_KEY_LAST
		);

		// Expose a function to quit/close the window to Lua.
		lua.set_function("Quit",
			[&]() {
				return gEngine.GetGraphicsManager().SetShouldQuit();
			}
		);

		// Expose the sound manager's ability to play sounds to 
		// Lua.
		lua.set_function("LoadSound", 
			[&](const string& name, const string& path) { 
				return gEngine.GetSoundManager().LoadSound(name, path); 
			} 
		);

		lua.set_function("PlaySound", 
			[&](const string& name) { 
				return gEngine.GetSoundManager().PlaySound(name); 
			} 
		);

		// Expose the graphics manager's ability to load sprites to
		// Lua.
		lua.set_function("LoadImage",
			[&](const string& name, const string& path) {
				return gEngine.GetGraphicsManager().LoadImage(name, path);
			}
		);

		// Expose the entity component system's functionality to
		// Lua.
		lua.set_function("CreateGameObject", 
			[&]() { 
				return gEngine.GetECS().Create(); 
			} 
		);

		lua.set_function("DestroyGameObject",
			[&](EntityID entity) {
				return gEngine.GetECS().Destroy(entity);
			}
		);

		lua.set_function("GetPosition",
			[&](EntityID entity) -> Position& {
				return gEngine.GetECS().Get<Position>(entity);
			}
		);

		lua.set_function("GetVelocity",
			[&](EntityID entity) -> Velocity& {
				return gEngine.GetECS().Get<Velocity>(entity);
			}
		);

		lua.set_function("GetGravity",
			[&](EntityID entity) -> Gravity& {
				return gEngine.GetECS().Get<Gravity>(entity);
			}
		);

		lua.set_function("GetSprite",
			[&](EntityID entity) -> Sprite& {
				return gEngine.GetECS().Get<Sprite>(entity);
			}
		);

		lua.set_function("GetHealth",
			[&](EntityID entity) -> Health& {
				return gEngine.GetECS().Get<Health>(entity);
			}
		);

		lua.set_function("GetScript",
			[&](EntityID entity) -> Script& {
				return gEngine.GetECS().Get<Script>(entity);
			}
		);

		// Since sol does not pass primitive Lua types (e.g. 
		// integer, float, string) we will have to resgister our 
		// game component structs with sol.
		lua.new_usertype<Position>("Position",
			sol::constructors<Position()>(),
			"x", &Position::x,
			"y", &Position::y
		);

		lua.new_usertype<Velocity>("Velocity",
			sol::constructors<Velocity()>(),
			"x", &Velocity::x,
			"y", &Velocity::y
		);

		lua.new_usertype<Gravity>("Gravity",
			sol::constructors<Gravity()>(),
			"meters_per_second", &Gravity::meters_per_second
		);

		lua.new_usertype<Sprite>("Sprite",
			sol::constructors<Sprite()>(),
			"image_name", &Sprite::image_name,
			"scale", &Sprite::scale,
			"rotation_axis", &Sprite::rotation_axis,
			"rotation_angle", &Sprite::rotation_angle,
			"z", &Sprite::z
		);

		lua.new_usertype<Health>("Health",
			sol::constructors<Health()>(),
			"percent", &Health::percent
		);

		lua.new_usertype<Script>("Script",
			sol::constructors<Script()>(),
			"name", &Script::name
		);

		// Expose vec2 and vec3 to Lua.
		lua.new_usertype<glm::vec3>("vec3",
			sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
			"x", &glm::vec3::x,
			"y", &glm::vec3::y,
			"z", &glm::vec3::z,
			// optional and fancy: operator overloading. see: https://github.com/ThePhD/sol2/issues/547
			sol::meta_function::addition, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; }),
			sol::meta_function::subtraction, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 - v2; }),
			sol::meta_function::multiplication, sol::overload(
				[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
				[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
				[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; }
			)
		);

		// Expose sol::state lua to users so they can call 
		// lua.new_usertype() for their own structs and 
		// lua.set_function() to expose their own functions.
		lua.set_function("lua",
			[&]() {
				return &lua;
			}
		);

		// Returns the width of the window
		lua.set_function("GetWindowWidth",
			[&]() {
				return gEngine.GetGraphicsManager().GetWindowWidth();
			}
		);

		// Returns the height of the window
		lua.set_function("GetWindowHeight",
			[&]() {
				return gEngine.GetGraphicsManager().GetWindowHeight();
			}
		);
	}

	void ScriptingManager::Shutdown() {
		
	}

	void ScriptingManager::Update() {
		ECS& ecs = gEngine.GetECS();

		ecs.ForEach<Script>( [&]( EntityID e ) {
			name_to_script_map[ecs.Get<Script>(e).name]();
		} );
	}

	bool ScriptingManager::LoadScript(const string& name, const string& p) {
		spdlog::info("Loading script: {}", p);
		
		if (name_to_script_map.count(name) == 0) {
			gEngine.GetResourceManager().SetRootPath("assets//scripts");
			path resolved_path = gEngine.GetResourceManager().ResolvePath(p);
			name_to_script_map[name] = lua.load_file(resolved_path.string().c_str());
			/*
			ECS& ecs = gEngine.GetECS();
			ecs.Get<Script>(ecs.Create()).name = name;
			*/
		}

		spdlog::info("Script loaded.");
		return true;
	}

	bool ScriptingManager::RunScript(const string& name) {
		if (name_to_script_map.count(name) != 0) {
			spdlog::info("Running script: {}.lua", name);
			name_to_script_map[name]();
			return true;
		}
		// Else print an error and return false
		else {
			spdlog::error("The {} script has not been loaded yet.", name);
			return false;
		}
	}
}
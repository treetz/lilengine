#pragma once // Used to ensure header files are not included multiple times

#include <memory>
#include <functional>

#include "Types.h"

namespace lilengine {
	using namespace Types;
	
	// Need to foward declare these classes so the compiler know the class exists and the getter methods can be used
	class GraphicsManager;
	class InputManager;
	class ResourceManager;
	class SoundManager;
	class ECS;
	class ScriptingManager;
	class TileMapManager;

	// The Engine class stores the managers for each of the engine's compnents, runs them, controls the game loop, and shuts the managers down
	class Engine {

		typedef std::function<void(Engine& e)> UpdateCallback;

	public:
		// Constructors for the Engine
		Engine(int window_width = 800, int window_height = 450, bool fullscreen = false); // Creates a small window by default
		~Engine();

		void Startup();
		void Shutdown();

		// Runs the engine's game loop
		void RunGameLoop(const UpdateCallback& callback);

		// Getter methods for each of the engine's managers
		GraphicsManager& GetGraphicsManager();
		InputManager& GetInputManager();
		ResourceManager& GetResourceManager();
		SoundManager& GetSoundManager();
		ECS& GetECS();
		ScriptingManager& GetScriptingManager();
		TileMapManager& GetTileMapManager();

	private:
		// Pimpl Pattern - Privately stores a unique pointer to the engine's implementation 
		class EngineImpl;
		std::unique_ptr< EngineImpl > impl_;
	};

	// Global Engine allows all managers to access all the other managers
	inline Engine gEngine;
}
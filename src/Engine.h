#pragma once

#include <memory>
#include <functional>

#include "Types.h"

namespace lilengine {
	using namespace Types;
	
	/* Need to foward declare these classes so the getter methods know the
	 * class exists and can be returned.
	 */
	class GraphicsManager;
	class InputManager;
	class ResourceManager;
	class SoundManager;
	class ECS;
	class ScriptingManager;
	class NetworkManager;
	class ChatBox;

	class Engine {

		typedef std::function<void(Engine& e)> UpdateCallback;

	public:
		Engine(int window_width = 800, int window_height = 450,
			bool fullscreen = false);
		~Engine();

		void Startup();
		void Shutdown();
		void RunGameLoop(const UpdateCallback& callback);
		GraphicsManager& GetGraphicsManager();
		InputManager& GetInputManager();
		ResourceManager& GetResourceManager();
		SoundManager& GetSoundManager();
		ECS& GetECS();
		ScriptingManager& GetScriptingManager();
		NetworkManager& GetNetworkManager();
		ChatBox& GetChatBox();

	private:
		class EngineImpl;
		std::unique_ptr< EngineImpl > impl_;
	};

	inline Engine gEngine;
}
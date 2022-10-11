#pragma once

#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "ECS.h"
#include "ScriptManager.h"
#include <thread>
#include <chrono>
#include <functional>

namespace Gengine {

	typedef std::function<void()> UpdateCallback;

	class Engine {
		public:
			Graphics::GraphicsManager graphics;
			Input::InputManager input;
			Sound::SoundManager sound;
			Resource::ResourceManager resource;
			Entity::ECS ecs;
			Script::ScriptManager script;

			void Startup(const UpdateCallback& callback);
			void Shutdown();
			void RunGameLoop(const UpdateCallback& callback);
	};

	inline Engine engine;
}

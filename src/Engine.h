#pragma once

#include <functional>
#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include <thread>
#include <chrono>

namespace Gengine {

	typedef std::function<void()> UpdateCallback;

	class Engine {
		public:
			void Startup(const UpdateCallback& callback);
			void Shutdown();
			void RunGameLoop(const UpdateCallback& callback);
	};
}

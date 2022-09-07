#pragma once

#include <functional>

namespace Gengine {

	typedef std::function<void()> UpdateCallback;

	class Engine {
		public:			
			void Startup();
			void Shutdown();
			void RunGameLoop();//const UpdateCallback& callback);

	};
}

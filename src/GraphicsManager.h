#pragma once

#include "Types.h"
#include "GLFW/glfw3.h"

namespace Graphics {

	class GraphicsManager {

		//private:
			//GLFWwindow* w;

		public:
			void GStartup(int window_width, int window_height, Foo::string window_name, bool window_fullscreen);
			void GShutdown();
			GLFWwindow* w;
	};
}

#pragma once

#include "GLFW/glfw3.h"
#include <algorithm>
#include <unordered_map>
#include "Types.h"
#include "sokol_gfx.h"
#include "stb_image.h"

namespace {
	struct Uniforms {
		glm::mat4 projection;
		glm::mat4 transform;
	};
}

namespace Graphics {

	struct Image {
		sg_image image;
		int width;
		int height;
	};

	class GraphicsManager {

		public:
			std::unordered_map<std::string, Image> imageMap;
			GLFWwindow* w;
			sg_bindings bindings;
			sg_pipeline pip;
			sg_pass_action pass_act;
			int wid, hei;
			Uniforms uniforms;

			void GStartup(int window_width, int window_height, Foo::string window_name, bool window_fullscreen);
			void GShutdown();
			void Draw();
			void loadImage(const std::string& name, const std::string& path);
			void destroyImage(const std::string& name);
	};
}

#include "GraphicsManager.h"
#include "spdlog/spdlog.h"

void Graphics::GraphicsManager::GStartup(int window_width, int window_height, Foo::string window_name, bool window_fullscreen) {
	glfwInit();
	// We'll use sokol_gfx's OpenGL backend
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	GLFWwindow* window = glfwCreateWindow( window_width, window_height, window_name.c_str(), window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0 );
	glfwSetWindowAspectRatio( window, window_width, window_height );
	w = window;

	if( !window ) {
		spdlog::error("Failed to create a window.");
 		glfwTerminate();
	}

	glfwMakeContextCurrent( window );
	glfwSwapInterval(1);
}

void Graphics::GraphicsManager::GShutdown() {
	glfwTerminate();
}

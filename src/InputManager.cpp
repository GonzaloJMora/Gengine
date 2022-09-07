#include "InputManager.h"
#include "spdlog/spdlog.h"

using namespace Input;

void Input::InputManager::Update() {
	glfwPollEvents();
}

bool Input::InputManager::isKeyPressed(GLFWwindow* window, int key) {
	return glfwGetKey(window, key);
}

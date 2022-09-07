#pragma once

#include "Types.h"
#include "GLFW/glfw3.h"

namespace Input {

        class InputManager {

            public:

                void Update();
			    bool isKeyPressed(GLFWwindow* window, int key);
        };
}

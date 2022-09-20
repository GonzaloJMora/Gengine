#pragma once

#include "GLFW/glfw3.h"
#include "Types.h"

namespace Input {

        class InputManager {

            public:

                void Update();
			    bool isKeyPressed(GLFWwindow* window, int key);
        };
}

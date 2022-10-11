#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Foo {
    typedef double real;
    typedef std::string string;
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;

    struct Position { glm::vec2 pos; };
    struct Velocity { glm::vec2 vel; };
    struct Gravity { real meters_per_second; };
    struct Health { real percent; };
    struct Script { string name; };
    struct Sound { string name; };
    struct Sprite {
        std::string name;
        glm::vec3 translate;
        glm::vec3 scale;
        glm::vec3 rotateAxis;
        float rotateAngle;
    };
}

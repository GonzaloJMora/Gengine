#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "Types.h"

namespace temp {
	struct Sprite {
		std::string name = "";
		glm::vec3 translate = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 rotateAxis = glm::vec3(0, 0, 0);
		float rotateAngle = 0.0;
	};

}

#endif
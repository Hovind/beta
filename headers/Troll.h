#pragma once

#include "Unit.h"

class Troll: public Unit {
public:
	Troll(float x, float y): Unit(x, y, 96.0f, 96.0f, 3, 160.0f, "textures/orc/troll.png", glm::uvec2(5, 11)) {}
};

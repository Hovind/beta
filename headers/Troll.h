#pragma once

#include "Unit.h"

class Troll: public Unit {
public:
	Troll(float x, float y): Unit(x, y, 32.0f, 32.0f, 90.0f, "textures/orc/troll.png") {}
	~Troll() {}
};

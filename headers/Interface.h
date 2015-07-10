#pragma once

#define GLM_FORCE_RADIANS

#include <set>
#include <glm/glm.hpp>

#include "SpriteBatch.h"

#include "Box.h"
#include "Unit.h"
#include "Map.h"

class Interface {
public:
	Interface();
	~Interface();

	void draw(Engine::SpriteBatch &spriteBatch) const;

	bool getBoxActive() const { return _box.getActive(); }
	void updateBox(glm::vec2 worldPosition);

	void clearTargets();
	void addTarget(Unit *unit);
	void updateTargets(Map &map, bool append);

	void drawTargetsUnitCircles(Engine::SpriteBatch &spriteBatch) const;

	void setTargetsDestination(Map &map, glm::vec2 destination) const;
private:
	Box _box;
	std::set<Unit*> _targets;
};

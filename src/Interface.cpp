#include "Interface.h"

Interface::Interface() {

}

Interface::~Interface() {

}

void Interface::draw(Engine::SpriteBatch &spriteBatch) {
	drawTargetsUnitCircles(spriteBatch);
	if (_box.getActive())
		_box.draw(spriteBatch);
}

bool Interface::getBoxActive() {
	return _box.getActive();
}

void Interface::updateBox(glm::vec2 mouseCoords) {
	if (_box.getActive())
		_box.update(mouseCoords);
	else
		_box.begin(mouseCoords);
}

void Interface::clearTargets() {
	_targets.clear();
}

void Interface::addTarget(Unit *unit) {
	_targets.insert(unit);
}

void Interface::updateTargets(Map &map, bool append) {
	glm::vec4 rect = _box.getRect();
	std::set<Unit*> units = map.getUnitsWithin(rect);

	if (append)
		for (auto it = units.begin(); it != units.end(); ++it)
			_targets.insert(*it);
	else
		_targets = units;

	_box.end();
}

void Interface::drawTargetsUnitCircles(Engine::SpriteBatch &spriteBatch) {
	for (auto it = _targets.begin(); it != _targets.end(); ++it)
		(*it)->drawUnitCircle(spriteBatch);
}

void Interface::setTargetsDestination(Map &map, glm::vec2 destination) {
	if (!map.getBlocked(destination))
		for (auto it = _targets.begin(); it != _targets.end(); ++it)
			map.setPath(*it, destination);

}

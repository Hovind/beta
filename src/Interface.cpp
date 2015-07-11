#include "Interface.h"

void Interface::draw(Engine::SpriteBatch &spriteBatch) const {
	drawTargetsUnitCircles(spriteBatch);
	if (m_box.getActive())
		m_box.draw(spriteBatch);
}


void Interface::updateBox(glm::vec2 worldPosition) {
	if (m_box.getActive())
		m_box.update(worldPosition);
	else
		m_box.begin(worldPosition);
}

void Interface::clearTargets() {
	m_targets.clear();
}

void Interface::addTarget(Unit *unit) {
	m_targets.insert(unit);
}

void Interface::updateTargets(Map &map, bool append) {
	glm::vec4 rect = m_box.getRect();
	std::set<Unit*> units = map.getUnitsWithin(rect);

	if (append)
		for (auto it = units.begin(); it != units.end(); ++it)
			m_targets.insert(*it);
	else
		m_targets = units;

	m_box.end();
}

void Interface::drawTargetsUnitCircles(Engine::SpriteBatch &spriteBatch) const {
	for (auto &it : m_targets)
		it->drawUnitCircle(spriteBatch);
}

void Interface::setTargetsDestination(Map &map, glm::vec2 destination) const {
	for (auto &it : m_targets)
		map.setPath(it, destination);

}

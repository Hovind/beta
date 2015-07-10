#include "IOManager.h"
#include "Map.h"
#include "Troll.h"
#include <iostream>

Map::Map(/*std::string mapFilePath*/)
: m_tileSize(32.0f)
/*, m_playerCapacity(2)
, m_playerSpawns(new glm::vec2[m_playerCapacity])*/ {
}


void Map::init() {
	glm::uvec2 mapSize = m_grid.getMapSize();
	for (unsigned int i = 0; i < mapSize.x * mapSize.y; ++i) {
		m_grid.setTexture(i, "textures/tiles/grass.png");
	}
	for (unsigned int i = 0; i < mapSize.x; ++i) {
		m_grid.setTexture(i, "textures/tiles/stone.png");
	}
	for (unsigned int i = 1; i < mapSize.x; ++i) {
		m_grid.setTexture(mapSize.x * mapSize.y - i, "textures/tiles/stone.png");
	}
	m_grid.setTexture(0, "textures/tiles/redgrass.png");
	glm::vec2 asd = getWorldPosition(getPosition(glm::vec2(0.0f, 0.0f)));
	spawn(new Troll(asd.x, asd.y));/*
	spawn(new Troll(120.0f, 0.0f));
	spawn(new Troll(120.0f, 120.0f));
	spawn(new Troll(0.0f, 120.0f));*/

}

void Map::update(float dt) {
	for (auto &unit : m_units) {
		setBlocked(unit->getPosition(), false);
		switch (unit->getState()) {
			case UnitState::STOP:
				break;
			case UnitState::MOVE:
				{
					glm::vec2
						currentWorldDestination = unit->getCurrentDestination(),
						finalWorldDestination = unit->getFinalDestination(),
						worldPosition = unit->getPosition();
					glm::uvec2
						finalDestination = getPosition(finalWorldDestination),
						position = getPosition(worldPosition);
					float speed = unit->getSpeed();
					if (getBlocked(finalWorldDestination))
						setPath(unit, getWorldPosition(m_grid.findNearestUnblockedPosition(finalDestination)));
					if (getBlocked(currentWorldDestination))
						updatePath(unit);

					if (position == finalDestination) {
						if (glm::length(finalWorldDestination - worldPosition) <= speed * dt) {
							unit->setPosition(finalWorldDestination);
							unit->setState(UnitState::STOP);
						} else {
							unit->moveFinal(dt);
						}

					} else {
						if (glm::length(currentWorldDestination - worldPosition) <= speed * dt)
							unit->setCurrentDestination(getWorldPosition(unit->popPath()));
						unit->moveCurrent(dt);
					}
					position = getPosition(unit->getPosition());
				}
				break;
			case UnitState::ATTACK:
				break;
		}
		setBlocked(unit->getPosition(), true);
	}
}

void Map::drawMap(Engine::SpriteBatch &spriteBatch) {
	glm::uvec2 mapSize = m_grid.getMapSize();
	for (unsigned int i = 0; i < mapSize.x * mapSize.y; ++i) {
		glm::vec2 position = getWorldPosition(i);
		glm::vec4 posAndSize = glm::vec4(position - 0.5f * glm::vec2(m_tileSize), m_tileSize, m_tileSize);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		Engine::GLTexture texture;
		if (getBlocked(position))
			texture = Engine::ResourceManager::getTexture("textures/tiles/redgrass.png");
		else
			texture = m_grid.getTexture(i);

		Engine::Color color;

		spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
	}
}
void Map::draw(Engine::SpriteBatch &spriteBatch) {
	drawMap(spriteBatch);
	for (auto it = m_units.begin(); it != m_units.end(); ++it)
		(*it)->draw(spriteBatch);
}

glm::vec4 Map::getBounds() {
	return glm::vec4(getWorldPosition(glm::uvec2(0, 0)), getWorldPosition(m_grid.getMapSize()));
}
std::set<Unit*> Map::getUnitsWithin(glm::vec4 rect) {
	std::set<Unit*> units;
	for (auto it = m_units.begin(); it != m_units.end(); ++it) {
		Unit* unit = *it;
		glm::vec2 size =  0.5f * unit->getSize();
		glm::vec2 position = unit->getPosition() + size;

		if (rect.x - 0.0f * size.x < position.x && position.x < rect.z + 2.0f * size.x && rect.y - 0.0f * size.y < position.y && position.y < rect.w + 2.0f * size.y)
			units.insert(unit);
	}
	return units;
}
void Map::spawn(Unit *unit) {
	m_units.insert(unit);
	m_grid.setBlocked(getPosition(unit->getPosition()), true);
}

void Map::updatePath(Unit *unit) {
	glm::uvec2 position = getPosition(unit);
	glm::uvec2 destination = getPosition(unit->getFinalDestination());
	unit->setPath(m_grid.getPath(position, destination));
	unit->setCurrentDestination(getWorldPosition(unit->popPath()));
}
void Map::setPath(Unit *unit, glm::vec2 finalDestination) {
	unit->setFinalDestination(finalDestination);
	updatePath(unit);
}

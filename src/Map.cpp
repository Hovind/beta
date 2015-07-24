#include "IOManager.h"
#include "Map.h"
#include "Troll.h"

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
	for (unsigned int i = 0; i < mapSize.x; ++i) {
		m_grid.setTexture(i * mapSize.x, "textures/tiles/redgrass.png");
	}
	for (unsigned int i = 1; i < mapSize.x; ++i) {
		m_grid.setTexture(i * mapSize.x - 1, "textures/tiles/redgrass.png");
	}

	spawn(new Troll(0.0f, 0.0f));
	spawn(new Troll(120.0f, 0.0f));
	spawn(new Troll(120.0f, 120.0f));
	spawn(new Troll(0.0f, 120.0f));

}

void Map::update(float dt) {
	for (auto &unit : m_units) {
		unsigned int size = unit->getGridSize();
		glm::vec2 oldPosition = unit->getPosition();
		setBlocked(oldPosition, size, false);
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

					if (getBlocked(finalWorldDestination, size))
						setPath(unit, getWorldPosition(m_grid.findNearestUnblockedPosition(finalDestination, size)));
					if (getBlocked(currentWorldDestination, size) || unit->getNeedsPathUpdate())
						updatePath(unit);

					if (position == finalDestination) {
						if (glm::length(finalWorldDestination - worldPosition) <= speed * dt)
							unit->move(finalWorldDestination);
						else
							unit->move(true, dt);
					} else {
						if (glm::length(currentWorldDestination - worldPosition) <= speed * dt)
							unit->setCurrentDestination(getWorldPosition(unit->popPath()));
						unit->move(false, dt);
					}
				}
				break;
			case UnitState::ATTACK:
				break;
		}
		unit->setAnimationTime(dt);
		glm::vec2 newPosition = unit->getPosition();
		setBlocked(newPosition, size, true);
		if (getPosition(oldPosition) != getPosition(newPosition))
			setAllNeedsPathUpdate(unit);

	}
}

void Map::drawMap(Engine::SpriteBatch &spriteBatch) {
	glm::uvec2 mapSize = m_grid.getMapSize();
	for (unsigned int i = 0; i < mapSize.x * mapSize.y; ++i) {
		glm::vec2 position = getWorldPosition(i);
		glm::vec4 posAndSize = glm::vec4(position - 0.5f * glm::vec2(m_tileSize), m_tileSize, m_tileSize);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

		Engine::Color color;

		spriteBatch.draw(posAndSize, uv, m_grid.getTexture(i).id, 0.0f, color);
	}
}
void Map::draw(Engine::SpriteBatch &spriteBatch) {
	drawMap(spriteBatch);
	for (auto &unit : m_units)
		unit->draw(spriteBatch);
}

glm::vec4 Map::getBounds() {
	return glm::vec4(getWorldPosition(glm::uvec2(0, 0)) - 0.5f * glm::vec2(m_tileSize), getWorldPosition(m_grid.getMapSize()) - 0.5f * glm::vec2(m_tileSize));
}
std::set<Unit*> Map::getUnitsWithin(glm::vec4 rect) {
	std::set<Unit*> units;
	for (auto &unit : m_units) {
		glm::vec2 size =  0.5f * unit->getDrawSize();
		glm::vec2 position = unit->getPosition() + size;

		if (rect.x - 0.0f * size.x < position.x && position.x < rect.z + 2.0f * size.x && rect.y - 0.0f * size.y < position.y && position.y < rect.w + 2.0f * size.y)
			units.insert(unit);
	}
	return units;
}
void Map::spawn(Unit *unit) {
	m_units.insert(unit);
	setBlocked(unit->getPosition(), unit->getGridSize(), true);
}

void Map::updatePath(Unit *unit) {
	glm::uvec2 position = getPosition(unit);
	glm::uvec2 destination = getPosition(unit->getFinalDestination());
	unit->setPath(m_grid.getPath(position, destination, unit->getGridSize()));
	unit->setCurrentDestination(getWorldPosition(unit->popPath()));
	unit->setNeedsPathUpdate(false);
}
void Map::setPath(Unit *unit, glm::vec2 finalDestination) {
	unit->setFinalDestination(finalDestination);
	unit->setNeedsPathUpdate(true);
}

void Map::setAllNeedsPathUpdate(Unit *currentUnit) {
	for (auto &unit : m_units)
		if (unit != currentUnit)
			unit->setNeedsPathUpdate(true);

}

#include "IOManager.h"
#include <iostream>
#include "Map.h"
#include "Troll.h"

Map::Map(/*std::string mapFilePath*/)
: _tileSize(32.0f)
, _tileList(_grid.getMapSize())
/*, _playerCapacity(2)
, _playerSpawns(new glm::vec2[_playerCapacity])*/ {

}

Map::~Map() {

}

unsigned int Map::getIndex(glm::vec2 worldPosition) {
	return _grid.getIndex(getPosition(worldPosition));
}

glm::uvec2 Map::getPosition(glm::vec2 worldPosition) {
	glm::uvec2 mapSize = _grid.getMapSize();
	return glm::uvec2((worldPosition.x + 0.5f * _tileSize * mapSize.x) / _tileSize, (worldPosition.y + 0.5f * _tileSize * mapSize.y) / _tileSize);
}
glm::uvec2 Map::getPosition(Unit *unit) {
	return getPosition(unit->getPosition());
}

glm::vec2 Map::getWorldPosition(glm::uvec2 position) {
	return glm::vec2(position) * _tileSize - 0.5f * glm::vec2(_grid.getMapSize()) * _tileSize + 0.5f * glm::vec2(_tileSize);
}
glm::vec2 Map::getWorldPosition(unsigned int index) {
	return getWorldPosition(_grid.getPosition(index));
}

bool Map::getBlocked(glm::vec2 worldPosition) {
	return _grid.getBlocked(getPosition(worldPosition));
}
void Map::setBlocked(glm::vec2 worldPosition, bool blocked) {
	_grid.setBlocked(getPosition(worldPosition), blocked);
}

void Map::init() {
	glm::uvec2 mapSize = _grid.getMapSize();
	for (unsigned int i = 0; i < mapSize.x * mapSize.y; ++i) {
		_tileList.setTexture(i, "textures/tiles/grass.png");
	}
	/*for (unsigned int i = 0; i < _mapSize.x; ++i) {
		_tileList.setTexture(i, "textures/tiles/stone.png");
	}
	for (unsigned int i = 1; i < _mapSize.x; ++i) {
		_tileList.setTexture(_mapSize.x * _mapSize.y - i, "textures/tiles/stone.png");
	}*/

	spawn(new Troll(0.0f, 0.0f));
	spawn(new Troll(120.0f, 0.0f));
	spawn(new Troll(120.0f, 120.0f));
	spawn(new Troll(0.0f, 120.0f));

}

void Map::update(float dt) {
	for (auto it = _units.begin(); it != _units.end(); ++it) {
		Unit *unit = *it;
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
						position = getPosition(worldPosition),
						newPosition;
					float speed = unit->getSpeed();

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
					newPosition = getPosition(unit->getPosition());
					if (newPosition != position) {
						_grid.setBlocked(position, false);
						_grid.setBlocked(newPosition, true);
					}
				}
				break;
			case UnitState::ATTACK:
				break;

		}
	}
}

void Map::drawMap(Engine::SpriteBatch &spriteBatch) {
	glm::uvec2 mapSize = _grid.getMapSize();
	for (unsigned int i = 0; i < mapSize.x * mapSize.y; ++i) {
		glm::vec2 position = getWorldPosition(i);

		glm::vec4 posAndSize = glm::vec4(position.x, position.y, _tileSize, _tileSize);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		Engine::GLTexture texture = _tileList.getTexture(i);
		Engine::Color color;

		spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
	}
}
void Map::draw(Engine::SpriteBatch &spriteBatch) {
	drawMap(spriteBatch);
	for (auto it = _units.begin(); it != _units.end(); ++it)
		(*it)->draw(spriteBatch);
}

glm::vec4 Map::getBounds() {
	return glm::vec4(getWorldPosition(glm::uvec2(0, 0)), getWorldPosition(_grid.getMapSize()));
}
std::set<Unit*> Map::getUnitsWithin(glm::vec4 rect) {
	std::set<Unit*> units;
	for (auto it = _units.begin(); it != _units.end(); ++it) {
		Unit* unit = *it;
		glm::vec2 size =  0.5f * unit->getSize();
		glm::vec2 position = unit->getPosition() + size;

		if (rect.x - 0.0f * size.x < position.x && position.x < rect.z + 2.0f * size.x && rect.y - 0.0f * size.y < position.y && position.y < rect.w + 2.0f * size.y)
			units.insert(unit);
	}
	return units;
}
void Map::spawn(Unit *unit) {
	_units.insert(unit);
	_grid.setBlocked(getPosition(unit->getPosition()), true);
}

void Map::updatePath(Unit *unit) {
	glm::uvec2 position = getPosition(unit);
	glm::uvec2 destination = getPosition(unit->getFinalDestination());
	unit->setPath(_grid.getPath(position, destination));
	unit->setCurrentDestination(getWorldPosition(unit->popPath()));
}
void Map::setPath(Unit *unit, glm::vec2 finalDestination) {
	unit->setFinalDestination(finalDestination);
	updatePath(unit);
}

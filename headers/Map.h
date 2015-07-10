#pragma once

#include <set>

#include "Unit.h"
#include "TileList.h"
#include "Grid.h"

class Map {
public:
	Map(/*std::string mapFilePath*/);
	~Map() {}


	unsigned int getIndex(glm::vec2 worldPosition) { return _grid.getIndex(getPosition(worldPosition)); }
	glm::uvec2 getPosition(glm::vec2 worldPosition) { glm::uvec2 mapSize = _grid.getMapSize(); return glm::uvec2((worldPosition.x + 0.5f * _tileSize * mapSize.x) / _tileSize, (worldPosition.y + 0.5f * _tileSize * mapSize.y) / _tileSize); }
	glm::uvec2 getPosition(Unit *unit) { return getPosition(unit->getPosition()); }
	glm::vec2 getWorldPosition(glm::uvec2 position) { return glm::vec2(position) * _tileSize - 0.5f * glm::vec2(_grid.getMapSize()) * _tileSize + 0.5f * glm::vec2(_tileSize); }
	glm::vec2 getWorldPosition(unsigned int index) { return getWorldPosition(_grid.getPosition(index)); }

	bool getBlocked(glm::vec2 worldPosition) { return _grid.getBlocked(getPosition(worldPosition)); }
	void setBlocked(glm::vec2 worldPosition, bool blocked) { _grid.setBlocked(getPosition(worldPosition), blocked); }

	void init();
	void update(float dt);

	void drawMap(Engine::SpriteBatch &spriteBatch);
	void draw(Engine::SpriteBatch &spriteBatch);

	glm::vec4 getBounds();
	std::set<Unit*> getUnitsWithin(glm::vec4 rect);
	void spawn(Unit *unit);

	void updatePath(Unit *unit);
	void setPath(Unit *unit, glm::vec2 finalDestination);
private:
	Grid _grid;

	float _tileSize;
	TileList _tileList;

	/*
	unsigned int _playerCapacity;
	glm::vec2 *_playerSpawns;
	*/
	std::set<Unit*> _units;
};

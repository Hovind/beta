#pragma once

#include <set>

#include "Unit.h"
#include "TileList.h"
#include "Grid.h"

class Map {
public:	
	Map(/*std::string mapFilePath*/);
	~Map();
	
	unsigned int getIndex(glm::vec2 worldPosition);

	glm::uvec2 getPosition(glm::vec2 worldPosition);
	glm::uvec2 getPosition(Unit *unit);

	glm::vec2 getWorldPosition(glm::uvec2 position);
	glm::vec2 getWorldPosition(unsigned int index);

	bool getBlocked(glm::vec2 worldPosition);
	void setBlocked(glm::vec2 worldPosition, bool blocked);

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
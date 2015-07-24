#pragma once

#include <set>

#include "Unit.h"
#include "Grid.h"

class Map {
public:
	Map(/*std::string mapFilePath*/);
	~Map() {}


	unsigned int getIndex(glm::vec2 worldPosition) { return m_grid.getIndex(getPosition(worldPosition)); }
	glm::uvec2 getPosition(glm::vec2 worldPosition) { glm::uvec2 mapSize = m_grid.getMapSize(); return glm::uvec2((worldPosition.x + 0.5f * m_tileSize * mapSize.x/* - 0.5f * m_tileSize*/) / m_tileSize, (worldPosition.y + 0.5f * m_tileSize * mapSize.y/* - 0.5f * m_tileSize*/) / m_tileSize); }
	glm::uvec2 getPosition(Unit *unit) { return getPosition(unit->getPosition()); }
	glm::vec2 getWorldPosition(glm::uvec2 position) { return glm::vec2(position) * m_tileSize - 0.5f * glm::vec2(m_grid.getMapSize()) * m_tileSize + 0.5f * glm::vec2(m_tileSize); }
	glm::vec2 getWorldPosition(unsigned int index) { return getWorldPosition(m_grid.getPosition(index)); }

	bool getBlocked(glm::vec2 worldPosition) { return m_grid.getBlocked(getPosition(worldPosition)); }
	bool getBlocked(glm::vec2 worldPosition, unsigned int size) { return m_grid.getBlocked(getPosition(worldPosition), size); }
	void setBlocked(glm::vec2 worldPosition, bool blocked) { m_grid.setBlocked(getPosition(worldPosition), blocked); }
	void setBlocked(glm::vec2 worldPosition, unsigned int size, bool blocked) { m_grid.setBlocked(getPosition(worldPosition), size, blocked); }

	void init();
	void update(float dt);

	void drawMap(Engine::SpriteBatch &spriteBatch);
	void draw(Engine::SpriteBatch &spriteBatch);

	glm::vec4 getBounds();
	std::set<Unit*> getUnitsWithin(glm::vec4 rect);
	void spawn(Unit *unit);

	void updatePath(Unit *unit);
	void setPath(Unit *unit, glm::vec2 finalDestination);
	void setAllNeedsPathUpdate(Unit *currentUnit);
private:
	Grid m_grid;
	float m_tileSize;
	/*
	unsigned int m_playerCapacity;
	glm::vec2 *m_playerSpawns;
	*/
	std::set<Unit*> m_units;
};

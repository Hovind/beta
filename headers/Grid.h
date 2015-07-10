#pragma once

#include <glm/glm.hpp>
#include <vector>

class Grid {
public:
	Grid();
	~Grid();

	glm::uvec2 getMapSize() const { return m_mapSize; }
	unsigned int getIndex(unsigned int x, unsigned int y) const { return x * m_mapSize.x + y; }
	unsigned int getIndex(glm::uvec2 position) const { return getIndex(position.x, position.y); }
	glm::uvec2 getPosition(unsigned int index) const { return glm::uvec2(index % m_mapSize.x, index / m_mapSize.x); }
	bool getValidIndex(glm::uvec2 position) const { return position.x < m_mapSize.x && position.y < m_mapSize.y; }
	unsigned int getHVal(glm::uvec2 start, glm::uvec2 end) const { return 10*(abs(end.x - start.x) + abs(end.y - start.y)); }
	bool getBlocked(glm::uvec2 position) const { return m_blocked[getIndex(position)]; }

	void setBlocked(glm::uvec2 position, bool blocked) { m_blocked[getIndex(position)] = blocked; }

	std::vector<glm::uvec2> getPath(glm::uvec2 start, glm::uvec2 end) const;
	glm::uvec2 findNearestUnblockedPosition(glm::uvec2 position) const;
private:
	glm::uvec2 m_mapSize;
	bool *m_blocked;
};

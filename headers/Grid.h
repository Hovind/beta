#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "ResourceManager.h"

class Grid {
public:
	Grid();
	~Grid() { delete[] m_blocked; delete[] m_textures; }

	glm::uvec2 getMapSize() const { return m_mapSize; }
	unsigned int getIndex(unsigned int x, unsigned int y) const { return x * m_mapSize.x + y; }
	unsigned int getIndex(glm::uvec2 position) const { return getIndex(position.x, position.y); }
	glm::uvec2 getPosition(unsigned int index) const { return glm::uvec2(index % m_mapSize.x, index / m_mapSize.x); }
	bool getValidIndex(glm::uvec2 position) const { return position.x < m_mapSize.x && position.y < m_mapSize.y; }
	unsigned int getHVal(glm::uvec2 start, glm::uvec2 end) const { return 10*(abs(end.x - start.x) + abs(end.y - start.y)); }

	bool getBlocked(glm::uvec2 position) const { return m_blocked[getIndex(position)]; }
	bool getBlocked(glm::uvec2 position, unsigned int size) const;
	Engine::GLTexture &getTexture(unsigned int index) const { return m_textures[index]; }

	void setTexture(unsigned int index, std::string texturePath) { m_textures[index] = Engine::ResourceManager::getTexture(texturePath); }
	void setBlocked(glm::uvec2 position, bool blocked) { m_blocked[getIndex(position)] = blocked; }
	void setBlocked(glm::uvec2 position, unsigned int size, bool blocked);

	std::vector<glm::uvec2> getPath(glm::uvec2 start, glm::uvec2 end, unsigned int size) const;
	glm::uvec2 findNearestUnblockedPosition(glm::uvec2 position, unsigned int size) const;
private:
	glm::uvec2 m_mapSize;
	unsigned int m_tileSize;

	bool *m_blocked;
	Engine::GLTexture *m_textures;
};

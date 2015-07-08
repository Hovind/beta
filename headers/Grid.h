#pragma once

#include <glm/glm.hpp>
#include <vector>

class Grid {
public:
	Grid();
	~Grid();


	glm::uvec2 getMapSize();
	unsigned int getIndex(unsigned int x, unsigned int y);
	unsigned int getIndex(glm::uvec2 position) ;
	glm::uvec2 getPosition(unsigned int index);

	unsigned int getHVal(glm::uvec2 start, glm::uvec2 end);
	bool getValidIndex(glm::uvec2 position);

	bool getBlocked(glm::uvec2 position);
	void setBlocked(glm::uvec2 position, bool blocked);

	std::vector<glm::uvec2> getPath(glm::uvec2 start, glm::uvec2 end);
private:
	glm::uvec2 _mapSize;
	bool *_blocked;
};
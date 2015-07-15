#include <algorithm>
#include "Grid.h"
#include "OpenSet.h"
#include "ClosedSet.h"
#include "GameException.h"


Grid::Grid()
: m_mapSize(glm::uvec2(50, 50))
, m_tileSize(2)
, m_blocked(new bool[m_mapSize.x * m_mapSize.y * m_tileSize])
, m_textures(new Engine::GLTexture[m_mapSize.x * m_mapSize.y]) {}

bool Grid::getBlocked(glm::uvec2 position, unsigned int size) const {
	const int radius = size / 2;
	for (int x = -radius; x <= radius; ++x) {
		for (int y = -radius; y <= radius; ++y) {
			if (getBlocked(position + glm::uvec2(x, y)))
				return true;
		}
	}
	return false;
}
void Grid::setBlocked(glm::uvec2 position, unsigned int size, bool blocked) {
	const int radius = size / 2;
	for (int x = -radius; x <= radius; ++x) {
		for (int y = -radius; y <= radius; ++y) {
			glm::uvec2 newPosition = position + glm::uvec2(x, y);
			if (getValidIndex(newPosition))
				setBlocked(newPosition, blocked);
		}
	}
}

std::vector<glm::uvec2> Grid::getPath(glm::uvec2 start, glm::uvec2 end, unsigned int size) const {
	ClosedSet closedSet;
	OpenSet openSet;

	Node *current = new Node(start, getHVal(start, end), 0, nullptr);
	openSet.insert(current);

	while (!openSet.empty()) {
		current = openSet.getFirst();
		glm::uvec2 currentPosition = current->getPosition();

		if (currentPosition == end){
			std::vector<glm::uvec2> path;
			while (current != nullptr) {
				path.push_back(current->getPosition());
				current = current->getParent();
			}
			return path;
		}

		closedSet.insert(current);
		openSet.remove(current);

		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				glm::uvec2 direction(x, y);
				glm::uvec2 position = currentPosition + direction;
				if (getValidIndex(position) && !getBlocked(position, size) && !closedSet.contains(position)){
					unsigned int gValTentative = current->getGVal() + (direction.x * direction.y) ? 14: 10;
					if (!openSet.contains(position)) {
						openSet.insert(new Node(position, getHVal(position, end), gValTentative, current));
					} else {
						Node *neighbour = openSet.get(position);
						if (gValTentative < neighbour->getGVal())
							neighbour->set(getHVal(position, end), gValTentative, current);
					}
				}
			}
 		}
	}
	throw GameException("You can not go there!");
}


glm::uvec2 Grid::findNearestUnblockedPosition(glm::uvec2 currentPosition, unsigned int size) const {
	for (unsigned int radius = 1; radius < m_mapSize.x * m_tileSize || radius < m_mapSize.y * m_tileSize; ++radius) {
		for (unsigned int i = 0; i <=radius; ++i) {
			glm::uvec2 position = currentPosition + glm::uvec2(-radius, i);
			if (getValidIndex(position) && !getBlocked(position, size))
				return position;

			position = currentPosition + glm::uvec2(i, radius);
			if (getValidIndex(position) && !getBlocked(position, size))
				return position;

			position = currentPosition + glm::uvec2(radius, -i);
			if (getValidIndex(position) && !getBlocked(position, size))
				return position;

			position = currentPosition + glm::uvec2(-i, -radius);
			if (getValidIndex(position) && !getBlocked(position, size))
				return position;
		}
	}
	throw GameException("You can not move!");
}

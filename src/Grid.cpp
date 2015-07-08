#include <set>

#include "Grid.h"
#include "OpenSet.h"
#include "ClosedSet.h"


Grid::Grid()
: _mapSize(glm::uvec2(200, 200))
, _blocked(new bool[_mapSize.x * _mapSize.y]) {}

Grid::~Grid() {

}


glm::uvec2 Grid::getMapSize() {
	return _mapSize;
}

unsigned int Grid::getIndex(unsigned int x, unsigned int y) {
	return x * _mapSize.x + y;
}

unsigned int Grid::getIndex(glm::uvec2 position) {
	return getIndex(position.x, position.y);
}

glm::uvec2 Grid::getPosition(unsigned int index) {
	return glm::uvec2(index % _mapSize.x, index / _mapSize.x);
}

bool Grid::getValidIndex(glm::uvec2 position) {
	return position.x < _mapSize.x && position.y < _mapSize.y;
}

unsigned int Grid::getHVal(glm::uvec2 start, glm::uvec2 end) {
	return 10*(abs(end.x - start.x) + abs(end.y - start.y));
}


bool Grid::getBlocked(glm::uvec2 position) {
	return _blocked[getIndex(position)];
}


void Grid::setBlocked(glm::uvec2 position, bool blocked) {
	_blocked[getIndex(position)] = blocked;
}


std::vector<glm::uvec2> Grid::getPath(glm::uvec2 start, glm::uvec2 end) {
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

		for (int x = -1; x <= 1; ++x){
			for (int y = -1; y <= 1; ++y) {
				glm::uvec2 direction(x, y);
				glm::uvec2 position = currentPosition + direction;
				if (getValidIndex(position) && !getBlocked(position) && !closedSet.contains(position)){
					unsigned int gValTentative = current->getGVal() + (direction.x * direction.y) ? 14: 10;
					if (!openSet.contains(position)) {
						openSet.insert(new Node(position, getHVal(position, end), gValTentative, current));
					}
					else {
						Node *neighbour = openSet.get(position);
						if (gValTentative < neighbour->getGVal()) {

							openSet.remove(neighbour);
							openSet.insert(new Node(position, getHVal(position, end), gValTentative, current));
						}
					}
				}
			}
 		}
	}
	return std::vector<glm::uvec2>();
}

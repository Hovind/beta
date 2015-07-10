#include <set>

#include "Grid.h"
#include "OpenSet.h"
#include "ClosedSet.h"
#include "GameException.h"


Grid::Grid()
: m_mapSize(glm::uvec2(200, 200))
, m_blocked(new bool[m_mapSize.x * m_mapSize.y]) {}

Grid::~Grid() {

}

std::vector<glm::uvec2> Grid::getPath(glm::uvec2 start, glm::uvec2 end) const {
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


glm::uvec2 Grid::findNearestUnblockedPosition(glm::uvec2 position) const {
	/*std::vector<glm::uvec> checked;
	for (int x = -1; x <= 1; ++x){
		for (int y = -1; y <= 1; ++y) {
			glm::uvec2 direction(x, y);
			glm::uvec2 destination = position + direction;
			checked.push_back(destination);
			if (!getBlocked(destination))
				return destination;
			else if (_grid.getValidIndex(destination) && [=](){for (auto &it : checked) if (it == destination) return false; return false; })
				return findNearestUnblockedPosition(destination);
		}
	}
	*/
	return position;
}

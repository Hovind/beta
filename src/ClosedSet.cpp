#include "ClosedSet.h"

ClosedSet::ClosedSet() {
	
}

ClosedSet::~ClosedSet() {
	for (auto it = _vector.begin(); it != _vector.end(); ++it)
		delete *it;
}

void ClosedSet::insert(Node *node) {
	_vector.push_back(node);
}

bool ClosedSet::contains(glm::uvec2 position) {
	for (auto it = _vector.begin(); it != _vector.end(); ++it) {
		if ((*it)->getPosition() == position) {
			return true;
		}
	}
	return false;
}
#include "OpenSet.h"

OpenSet::OpenSet() {
}

OpenSet::~OpenSet() {
	for (auto it = _vector.begin(); it != _vector.end(); ++it)
		delete *it;
}

bool OpenSet::empty() {
	return _vector.empty();
}

Node *OpenSet::getFirst() {
	return _vector.front();
}

Node *OpenSet::get(glm::uvec2 position) {
	for (auto it = _vector.begin(); it != _vector.end(); ++it) {
		if ((*it)->getPosition() == position) {
			return *it;
		}
	}
	return new Node(position, 0, 0, nullptr);
}

bool OpenSet::contains(glm::uvec2 position) {
	for (auto it = _vector.begin(); it != _vector.end(); ++it) {
		if ((*it)->getPosition() == position)
			return true;
	}
	return false;
}

void OpenSet::insert(Node *node) {
	unsigned int fVal = node->getFVal();
	auto it = _vector.begin();
	while (it != _vector.end() && (*it)->getFVal() < fVal)
		++it;
	_vector.insert(it, node);
}

void OpenSet::remove(Node *node) {
	auto it = _vector.begin();
	while (*it != node)
		++it;
	_vector.erase(it);
}
#include "OpenSet.h"

Node *OpenSet::get(glm::uvec2 position) const {
	for (auto &it : m_vector)
		if (it->getPosition() == position)
			return it;
	return new Node(position, 0, 0, nullptr);
}

bool OpenSet::contains(glm::uvec2 position) const {
	for (auto &it : m_vector)
		if (it->getPosition() == position)
			return true;
	return false;
}

void OpenSet::insert(Node *node) {
	unsigned int fVal = node->getFVal();
	auto it = m_vector.begin();
	while (it != m_vector.end() && (*it)->getFVal() < fVal)
		++it;
	m_vector.insert(it, node);
}

void OpenSet::remove(Node *node) {
	auto it = m_vector.begin();
	while (*it != node)
		++it;
	m_vector.erase(it);
}

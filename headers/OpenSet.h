#pragma once

#include <vector>

#include "Node.h"

class OpenSet {
public:
	OpenSet() {}
	~OpenSet() { for (auto &it : m_vector) delete it; }

	bool empty() const { return m_vector.empty(); }
	Node *getFirst() const { return m_vector.front(); }

	Node *get(glm::uvec2 position) const;
	bool contains(glm::uvec2 position) const;

	void insert(Node *node);
	void remove(Node *node);

private:
	std::vector<Node*> m_vector;
};

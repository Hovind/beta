#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Node.h"

class ClosedSet {
public:
	ClosedSet();
	~ClosedSet();

	void insert(Node *node);
	bool contains(glm::uvec2 position) const;


private:
	std::vector<Node*> _vector;
};

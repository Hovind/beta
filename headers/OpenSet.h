#pragma once

#include <vector>

#include "Node.h"

class OpenSet {
public:
	OpenSet();
	~OpenSet();

	bool empty();
	Node *getFirst();

	Node *get(glm::uvec2 position);
	bool contains(glm::uvec2 position);

	void insert(Node *node);
	void remove(Node *node);

private:
	std::vector<Node*> _vector;
};
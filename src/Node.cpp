#include "Node.h"

Node::Node(glm::uvec2 position, unsigned int hVal, unsigned int gVal, Node *parent)
: m_position(position)
, m_hVal(hVal)
, m_gVal(gVal)
, m_parent(parent) {}

Node::~Node() {

}

void Node::set(unsigned int hVal, unsigned int gVal, Node *parent) {
	setHVal(hVal);
	setGVal(gVal);
	setParent(parent);
}


bool Node::operator<(const Node &rhs) const {
	return this->getFVal() < rhs.getFVal();
}

bool Node::operator==(const Node &rhs) const {
	return this->getPosition() == rhs.getPosition();
}

bool Node::operator!=(const Node &rhs) const {
	return !(*this == rhs);
}

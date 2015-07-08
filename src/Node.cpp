#include "Node.h"

Node::Node(glm::uvec2 position, unsigned int hVal, unsigned int gVal, Node *parent)
: _position(position)
, _hVal(hVal)
, _gVal(gVal)
, _parent(parent) {}

Node::~Node() {

}

glm::uvec2 Node::getPosition() const {
	return _position;
}
unsigned int Node::getHVal() const {
	return _hVal;
}
unsigned int Node::getGVal() const {
	return _gVal;
}
unsigned int Node::getFVal() const {
	return getHVal() + getGVal();
}
Node *Node::getParent() const {
	return _parent;
}

void Node::setHVal(unsigned int hVal) {
	_hVal = hVal;
}
void Node::setGVal(unsigned int gVal) {
	_gVal = gVal;
}
void Node::setParent(Node *parent) {
	_parent = parent;
}

void Node::set(unsigned int hVal, unsigned int gVal, Node *parent) {
	setHVal(hVal);
	setGVal(gVal);
	setParent(parent);
}


bool Node::operator<(const Node &rhs) {
	return this->getFVal() < rhs.getFVal();
}

bool Node::operator==(const Node &rhs) {
	return this->getPosition() == rhs.getPosition();
}

bool Node::operator!=(const Node &rhs) {
	return !(*this == rhs);
}
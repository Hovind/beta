#pragma once

#include <glm/glm.hpp>

class Node {
	public:
		Node(glm::uvec2 position, unsigned int hVal, unsigned int gVal, Node *parent);
		~Node();

		glm::uvec2 getPosition() const;
		unsigned int getHVal() const;
		unsigned int getGVal() const;
		unsigned int getFVal() const;
		Node *getParent() const;

		void setPosition(glm::uvec2 position);
		void setHVal(unsigned int hVal);
		void setGVal(unsigned int gVal);
		void setParent(Node *parent);

		void set(unsigned int hVal, unsigned int gVal, Node *parent);

		bool operator<(const Node &rhs);
		bool operator==(const Node &rhs);
		bool operator!=(const Node &rhs);
	private:
		glm::uvec2 _position;
		unsigned int
			_hVal,
			_gVal;
		Node *_parent;
};
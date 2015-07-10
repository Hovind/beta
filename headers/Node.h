#pragma once

#include <glm/glm.hpp>

class Node {
	public:
		Node(glm::uvec2 position, unsigned int hVal, unsigned int gVal, Node *parent);
		~Node();

		glm::uvec2 getPosition() const { return m_position; }
		unsigned int getHVal() const { return m_hVal; }
		unsigned int getGVal() const { return m_gVal; }
		unsigned int getFVal() const { return getHVal() + getGVal(); }
		Node *getParent() const { return m_parent; }

		void setHVal(unsigned int hVal) { m_hVal = hVal; }
		void setGVal(unsigned int gVal) { m_gVal = gVal; }
		void setParent(Node *parent) { m_parent = parent; }

		void set(unsigned int hVal, unsigned int gVal, Node *parent);

		bool operator<(const Node &rhs) const;
		bool operator==(const Node &rhs) const;
		bool operator!=(const Node &rhs) const;
	private:
		glm::uvec2 m_position;
		unsigned int
			m_hVal,
			m_gVal;
		Node *m_parent;
};

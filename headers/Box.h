#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include "SpriteBatch.h"
#include "GLTexture.h"

class Box {
public:
	Box();
	~Box();

	void begin(glm::vec2 worldPosition);
	void end();
	void update(glm::vec2 worldPosition);

	bool getActive() const { return m_active; }
	glm::vec4 getRect();

	void draw(Engine::SpriteBatch &spriteBatch) const;

	private:
		bool m_active;
		glm::vec4 m_rect;

};

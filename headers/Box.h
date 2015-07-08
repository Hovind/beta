#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include "SpriteBatch.h"
#include "GLTexture.h"

class Box {
public:
	Box();
	~Box();

	void begin(glm::vec2 pos);
	void end();
	void update(glm::vec2 pos);

	bool getActive();
	glm::vec4 getRect();

	void draw(Engine::SpriteBatch& spriteBatch);

	private:
		bool _active;
		glm::vec4 _rect;

};
#pragma once

#define GLM_FORCE_RADIANS

#include <string>
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "SpriteSheet.h"


class Object {
public:
	Object(float x, float y, float width, float height, unsigned int gridSize, bool clickAble, std::string spriteSheetPath, glm::uvec2 spriteSheetDimensions);
	~Object() {}


	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getDrawSize() const { return m_drawSize; }
	glm::vec4 getDrawPositionAndSize() const { return glm::vec4(m_position - 0.5f * m_drawSize, m_drawSize); }
    unsigned int getGridSize() const { return m_gridSize; }/*

    Engine::SpriteSheet getSpriteSheet() const { return m_spriteSheet; }
    */void setPosition(glm::vec2 position) { m_position = position; }
    //Engine::SpriteSheet getSpriteSheet() const { return m_spriteSheet; }
	virtual void draw(Engine::SpriteBatch &spriteBatch) const = 0;


    Engine::SpriteSheet getSpriteSheet() const { return m_spriteSheet; }

protected:
	glm::vec2
		m_drawSize,
		m_position;
	unsigned int m_gridSize;
    bool m_clickAble;

	Engine::SpriteSheet m_spriteSheet;
};

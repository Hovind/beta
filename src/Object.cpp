/*#define GLM_FORCE_RADIANS

#include <iostream>
#include <glm/gtx/string_cast.hpp>*/
#include "Object.h"
#include "ResourceManager.h"

Object::Object(float x, float y, float width, float height, unsigned int gridSize, bool clickAble, std::string spriteSheetPath, glm::uvec2 spriteSheetDimensions)
: m_drawSize(glm::vec2(width, height))
, m_position(glm::vec2(x, y))
, m_gridSize(gridSize)
, m_clickAble(clickAble) {
	m_spriteSheet.init(spriteSheetPath, spriteSheetDimensions);
}

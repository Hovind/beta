/*#define GLM_FORCE_RADIANS

#include <iostream>
#include <glm/gtx/string_cast.hpp>*/
#include "Unit.h"
#include "ResourceManager.h"

Unit::Unit(float x, float y, float width, float height, unsigned int gridSize, float speed, std::string spriteSheetPath, glm::uvec2 spriteSheetDimensions)
: m_drawSize(glm::vec2(width, height))
, m_position(glm::vec2(x, y))
, m_currentDestination(m_position)
, m_finalDestination(m_position)
, m_animationTime(0)
, m_animationSpeed(6.0f)
, m_needsPathUpdate(false)
, m_gridSize(gridSize)
, m_speed(speed)
, m_state(UnitState::STOP) {
	m_circleTexture = Engine::ResourceManager::getTexture("textures/misc/circle.png");
	m_spriteSheet.init(spriteSheetPath, spriteSheetDimensions);
}

void Unit::move(bool final, float dt) {
	m_velocity = glm::normalize((final ? m_finalDestination : m_currentDestination) - m_position) * m_speed;
	m_position += m_velocity * dt;
}
void Unit::move(glm::vec2 destination) {
	m_position = destination;
	m_state = UnitState::STOP;

}
glm::uvec2 Unit::popPath() {
	m_path.pop_back();
	return m_path.back();
}

void Unit::draw(Engine::SpriteBatch& spriteBatch) const {
	Engine::Color color;
	glm::vec4 posAndSize = getDrawPositionAndSize();
	unsigned int index = 54;
	const float FRACTION = 0.4f * m_speed;
	const unsigned int FRAMES = 4;
	switch (m_state) {
		case UnitState::STOP:
		{
			if (m_velocity.y > FRACTION) {
				if (abs(m_velocity.x) > FRACTION) {
					index = 51;
				} else {
					index = 50;
				}
			} else if (m_velocity.y < -FRACTION) {
				if (abs(m_velocity.y) > FRACTION) {
					index = 53;
				} else {
					index = 54;
				}
			} else {
				index = 52;
			}
		}
		break;
		case UnitState::MOVE:
		{
			if (m_velocity.y > FRACTION) {
				if (abs(m_velocity.x) > FRACTION) {
					index = 46;
				} else {
					index = 45;
				}
			} else if (m_velocity.y < - FRACTION) {
				if (abs(m_velocity.x) > FRACTION) {
					index = 48;
				} else {
					index = 49;
				}
			} else {
				index = 47;
			}
			index -= m_spriteSheet.getDimensions().x * (static_cast<unsigned int>(m_animationTime * m_animationSpeed) % FRAMES);
		}
		break;

	}
	glm::vec4 uv = m_spriteSheet.getUVs(index);
	if (m_velocity.x < 0) {
		uv.x += 1.0f / m_spriteSheet.getDimensions().x;
		uv.z *= - 1.0f;
	}
	spriteBatch.draw(posAndSize, uv, m_spriteSheet.getTexture().id, 0.0f, color);
}
void Unit::drawUnitCircle(Engine::SpriteBatch& spriteBatch) const {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color;
	glm::vec4 posAndSize = getDrawPositionAndSize();
	posAndSize.w *= 0.5f;

	spriteBatch.draw(posAndSize, uv, m_circleTexture.id, 0.0f, color);
}

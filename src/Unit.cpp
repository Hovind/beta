#include "Unit.h"
#include "ResourceManager.h"
#include <iostream>
Unit::Unit(float x, float y, float width, float height, float speed, std::string texturePath)
: m_size(glm::vec2(width, height))
, m_position(glm::vec2(x, y))
, m_currentDestination(m_position)
, m_finalDestination(m_position)
, m_speed(speed)
, m_state(UnitState::STOP) {
	m_circleTexture = Engine::ResourceManager::getTexture("textures/misc/circle.png");
	m_texture = Engine::ResourceManager::getTexture(texturePath);
}

glm::vec2 Unit::moveCurrent(float dt) {
	glm::vec2 currentDifference = m_currentDestination - m_position;
	m_velocity = glm::normalize(currentDifference) * m_speed;
	m_position += m_velocity * dt;
	return m_position;
}
glm::vec2 Unit::moveFinal(float dt) {
	glm::vec2 finalDifference = m_finalDestination - m_position;
	std::cout << glm::length(finalDifference) << std::endl;
	m_velocity = glm::normalize(finalDifference) * m_speed;
	m_position += m_velocity * dt;
	return m_position;
}
glm::uvec2 Unit::popPath() {
	m_path.pop_back();
	return m_path.back();
}

void Unit::draw(Engine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color;
	glm::vec4 posAndSize = getDrawPositionAndSize();

	spriteBatch.draw(posAndSize, uv, m_texture.id, 0.0f, color);
}
void Unit::drawUnitCircle(Engine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color;
	glm::vec4 posAndSize = getDrawPositionAndSize();
	posAndSize.w *= 0.5f;

	spriteBatch.draw(posAndSize, uv, m_circleTexture.id, 0.0f, color);
}

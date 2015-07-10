#include "Box.h"

#include "ResourceManager.h"

Box::Box()
: m_active(false) {
}
Box::~Box() {

}

void Box::begin(glm::vec2 worldPosition) {
	m_rect = glm::vec4(worldPosition, worldPosition);
	m_active = true;
}
void Box::end() {
	m_active = false;
}
void Box::update(glm::vec2 worldPosition) {
	m_rect = glm::vec4(m_rect.x, m_rect.y, worldPosition);
}


glm::vec4 Box::getRect() {
	if (m_rect.x > m_rect.z)
		std::swap(m_rect.x, m_rect.z);
	if (m_rect.y > m_rect.w)
		std::swap(m_rect.y, m_rect.w);
	return m_rect;
}

void Box::draw(Engine::SpriteBatch& spriteBatch) const {
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("textures/misc/box.png");

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color(0, 255, 0, 127);
	glm::vec4 positionAndSize = m_rect - glm::vec4(0, 0, m_rect.x, m_rect.y);

	spriteBatch.draw(positionAndSize, uv, texture.id, 0.0f, color);
}

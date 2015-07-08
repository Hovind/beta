#include <string>
#include "Box.h"

#include "ResourceManager.h"

Box::Box()
: _active(false) {
}
Box::~Box() {

}

void Box::begin(glm::vec2 pos) {
	_rect = glm::vec4(pos.x, pos.y, pos.x, pos.y);
	_active = true;
}
void Box::end() {
	_active = false;
}
void Box::update(glm::vec2 pos) {
	_rect = glm::vec4(_rect.x, _rect.y, pos.x, pos.y);
}

bool Box::getActive() {
	return _active;
}

glm::vec4 Box::getRect() {
	if (_rect.x > _rect.z)
		std::swap(_rect.x, _rect.z);
	if (_rect.y > _rect.w)
		std::swap(_rect.y, _rect.w);
	return _rect;
}

void Box::draw(Engine::SpriteBatch& spriteBatch) {
	static Engine::GLTexture texture = Engine::ResourceManager::getTexture("textures/misc/box.png");

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color(0, 255, 0, 127);
	glm::vec4 positionAndSize = _rect - glm::vec4(0, 0, _rect.x, _rect.y);

	spriteBatch.draw(positionAndSize, uv, texture.id, 0.0f, color);
}
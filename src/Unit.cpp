#include "Unit.h"
#include "ResourceManager.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Unit::Unit(float x, float y, float width, float height, float speed, std::string texturePath)
: _size(glm::vec2(width, height))
, _position(glm::vec2(x, y))
, _currentDestination(_position)
, _finalDestination(_position)
, _speed(speed)
, _state(UnitState::STOP) {
	_circleTexture = Engine::ResourceManager::getTexture("textures/misc/circle.png");
	_texture = Engine::ResourceManager::getTexture(texturePath);
}

Unit::~Unit() {

}


glm::vec2 Unit::moveCurrent(float dt) {
	glm::vec2 currentDifference = _currentDestination - _position;
	_velocity = glm::normalize(currentDifference) * _speed;
	_position += _velocity * dt;
	return _position;
}

glm::vec2 Unit::moveFinal(float dt) {
	glm::vec2 finalDifference = _finalDestination - _position;
	_velocity = glm::normalize(finalDifference) * _speed;
	_position += _velocity * dt;
	return _position;
}

glm::uvec2 Unit::popPath() {
	_path.pop_back();
	return _path.back();
}

void Unit::setPath(std::vector<glm::uvec2> path) {
	_path = path;
}

void Unit::setState(UnitState state) {
	_state = state;
}

void Unit::setPosition(glm::vec2 position) {
	_position = position;
}

void Unit::setCurrentDestination(glm::vec2 currentDestination) {
	_currentDestination = currentDestination;
}

void Unit::setFinalDestination(glm::vec2 finalDestination) {
	_finalDestination = finalDestination;
	_state = UnitState::MOVE;
}

void Unit::draw(Engine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color;
	glm::vec4 posAndSize = getDrawPositionAndSize();

	spriteBatch.draw(posAndSize, uv, _texture.id, 0.0f, color);
}

void Unit::drawUnitCircle(Engine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::Color color;
	glm::vec4 posAndSize = getDrawPositionAndSize();
	posAndSize.w *= 0.5f;

	spriteBatch.draw(posAndSize, uv, _circleTexture.id, 0.0f, color);
}



glm::vec2 Unit::getPosition() {
	return _position;
}

glm::vec2 Unit::getCurrentDestination() {
	return _currentDestination;
}

glm::vec2 Unit::getFinalDestination() {
	return _finalDestination;
}

glm::vec2 Unit::getSize() {
	return _size;
}

glm::vec4 Unit::getDrawPositionAndSize() {
	return glm::vec4(_position.x - 0.5f * _size.x, _position.y - 0.5f * _size.y, _size.x, _size.y);
}

UnitState Unit::getState() {
	return _state;
}
float Unit::getSpeed() {
	return _speed;
}

#pragma once

#define GLM_FORCE_RADIANS

#include <string>
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"

enum class UnitState {STOP, MOVE, ATTACK};

class Unit {
public:
	Unit(float x, float y, float width, float height, float speed, std::string texturePath);
	~Unit();

	glm::vec2 moveCurrent(float dt);
	glm::vec2 moveFinal(float dt);
	glm::uvec2 popPath();

	void setPath(std::vector<glm::uvec2> path);
	void setState(UnitState state);

	void setPosition(glm::vec2 position);
	void setCurrentDestination(glm::vec2 currentDestination);
	void setFinalDestination(glm::vec2 finalDestination);


	glm::vec2 getPosition();
	glm::vec2 getCurrentDestination();
	glm::vec2 getFinalDestination();
	glm::vec2 getSize();
	glm::vec4 getDrawPositionAndSize();

	UnitState getState();
	float getSpeed();

	void draw(Engine::SpriteBatch &spriteBatch);
	void drawUnitCircle(Engine::SpriteBatch& spriteBatch);

private:
	glm::vec2
		_size,
		_position,
		_velocity,
		_currentDestination,
		_finalDestination;

	float _speed;
	UnitState _state;
	std::vector<glm::uvec2> _path;

	Engine::GLTexture
		_circleTexture,
		_texture;
};

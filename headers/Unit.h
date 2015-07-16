#pragma once

#define GLM_FORCE_RADIANS

#include <string>
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "SpriteSheet.h"

enum class UnitState {STOP, MOVE, ATTACK};

class Unit {
public:
	Unit(float x, float y, float width, float height, unsigned int gridSize, float speed, std::string spriteSheetPath, glm::uvec2 spriteSheetDimensions);
	~Unit() {}

	void move(bool final, float dt);
	void move(glm::vec2 destination);
	glm::uvec2 popPath();

	void setNeedsPathUpdate(bool needsPathUpdate) { m_needsPathUpdate = needsPathUpdate; }
	void setPath(std::vector<glm::uvec2> path) { m_path = path; }
	void setState(UnitState state) { m_state = state; }
	void setPosition(glm::vec2 position) { m_position = position; }
	void setCurrentDestination(glm::vec2 currentDestination) { m_currentDestination = currentDestination; }
	void setFinalDestination(glm::vec2 finalDestination) { m_finalDestination = finalDestination; m_state = UnitState::MOVE; }
	void setDirection(glm::uvec2 direction) { m_direction = direction; }

	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getCurrentDestination() const { return m_currentDestination; }
	glm::vec2 getFinalDestination() const { return m_finalDestination; }
	glm::vec2 getDrawSize() const { return m_drawSize; }
	glm::vec4 getDrawPositionAndSize() const { return glm::vec4(m_position - 0.5f * m_drawSize, m_drawSize); }

	bool getNeedsPathUpdate() const { return m_needsPathUpdate; }
	unsigned int getGridSize() const { return m_gridSize; }
	float getSpeed() const { return m_speed; }
	UnitState getState() const { return m_state; }

	void draw(Engine::SpriteBatch &spriteBatch) const;
	void drawUnitCircle(Engine::SpriteBatch& spriteBatch) const;

private:
	glm::vec2
		m_drawSize,
		m_position,
		m_velocity,
		m_currentDestination,
		m_finalDestination;
	glm::uvec2 m_direction;
	bool m_needsPathUpdate;
	unsigned int m_gridSize;
	float m_speed;
	UnitState m_state;
	std::vector<glm::uvec2> m_path;

	Engine::GLTexture m_circleTexture;
	Engine::SpriteSheet m_spriteSheet;
};

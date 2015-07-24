#pragma once

#include "Object.h"

enum class UnitState {STOP, MOVE, ATTACK};

class Unit : public Object {
friend class Map;
public:
	Unit(float x, float y, float width, float height, unsigned int gridSize, float speed, std::string spriteSheetPath, glm::uvec2 spriteSheetDimensions);
	~Unit() {}

	void move(bool final, float dt);
	void move(glm::vec2 destination);
	glm::uvec2 popPath();

	void setAnimationTime(float dt) { m_animationTime += dt; }
	void setNeedsPathUpdate(bool needsPathUpdate) { m_needsPathUpdate = needsPathUpdate; }
	void setPath(std::vector<glm::uvec2> path) { m_path = path; }
	void setState(UnitState state) { m_state = state; m_animationTime = 0; }
	void setCurrentDestination(glm::vec2 currentDestination) { m_currentDestination = currentDestination; }
	void setFinalDestination(glm::vec2 finalDestination) { m_finalDestination = finalDestination; m_state = UnitState::MOVE; }

	glm::vec2 getCurrentDestination() const { return m_currentDestination; }
	glm::vec2 getFinalDestination() const { return m_finalDestination; }

	bool getNeedsPathUpdate() const { return m_needsPathUpdate; }
	float getSpeed() const { return m_speed; }
	UnitState getState() const { return m_state; }

	virtual void draw(Engine::SpriteBatch &spriteBatch) const;
	void drawUnitCircle(Engine::SpriteBatch& spriteBatch) const;

private:
	glm::vec2
		m_velocity,
		m_currentDestination,
		m_finalDestination;
	float
		m_animationTime,
		m_animationSpeed;
	bool m_needsPathUpdate;
	float m_speed;
	UnitState m_state;
	std::vector<glm::uvec2> m_path;

	Engine::GLTexture m_circleTexture;
};

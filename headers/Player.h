#pragma once

enum class Race {HUMAN, NIGHTELF, ORC, UNDEAD};

class Player {
public:
	Player();
	~Player();

	void spawn(glm::vec2 position);
private:
	Race _race;
}

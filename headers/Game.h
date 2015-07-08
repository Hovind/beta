#pragma once

#include <vector>

#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "InputManager.h"
#include "SpriteBatch.h"
#include "Time.h"

#include "Interface.h"
#include "Map.h"
#include "Unit.h"
#include "Box.h"

enum class GameState {PLAY, EXIT};

class Game {
public:
	Game();
	~Game();

	void run();

private:
	void initSystems();
	void updateResolution(int screenWidth, int screenHeight);
	void initShaders();
	void gameLoop();
	void processInput();
	void draw();

	int _screenWidth,
		_screenHeight;

	Interface _interface;
	Map _map;
	GameState _gameState;


	Engine::Window _window;
	Engine::Time _time;
	Engine::GLSLProgram _colorProgram;
	Engine::Camera2D _camera;
	Engine::InputManager _inputManager;
	Engine::SpriteBatch _spriteBatch;
};


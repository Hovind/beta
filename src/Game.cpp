#include <algorithm>
#include <iostream>

#include "Game.h"
#include "Exception.h"
#include "Engine.h"
#include "ResourceManager.h"

Game::Game()
: _screenWidth(1366)
, _screenHeight(768)
, _gameState(GameState::PLAY)
, _camera(_screenWidth, _screenHeight) {}

Game::~Game()
{
}

void Game::run() {
	initSystems();
	_map.init();
	gameLoop();
}

void Game::initSystems() {
	Engine::init();
	_window.create("Alpha Game Engine", _screenWidth, _screenHeight, /*0);//*/Engine::WindowFlags::FULLSCREEN);
	int screenWidth = _window.getScreenWidth();
	int screenHeight = _window.getScreenHeight();

	std::cout << "Width: " << screenWidth << " Height: " << screenHeight << std::endl;
	//updateResolution(screenWidth, screenHeight);
	initShaders();
	_spriteBatch.init();
}

void Game::updateResolution(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_camera.updateResolution(_screenWidth, _screenHeight);
}

void Game::initShaders() {
	_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void Game::gameLoop() {

	float dt = _time.getFrameCap();
	while (_gameState != GameState::EXIT) {
		_time.begin();
		processInput();
		_map.update(dt);
		_camera.update();
		draw();

		dt = _time.end();
	}
}

void Game::processInput() {
	SDL_Event event;

	const float CAMERA_SPEED = 4.0f;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x, event.motion.y);
				break;
			case SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}
	}

	glm::vec2 mouseCoords = _inputManager.getMouseCoords();
	glm::vec2 worldCoords = _camera.convertScreenToWorld(mouseCoords);
	//std::cout << "X: " << mouseCoords.x << " Y: " << mouseCoords.y << std::endl;

	glm::vec2 lowerBounds = 0.1f * glm::vec2(_screenWidth, _screenHeight);
	glm::vec2 upperBounds = 0.9f * glm::vec2(_screenWidth, _screenHeight);

	glm::vec4 mapBounds = _map.getBounds();
	glm::vec2 cameraPosition = _camera.getPosition();

	if (mouseCoords.x <  lowerBounds.x && mapBounds.x < cameraPosition.x - 0.5f * _screenWidth) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (mouseCoords.x > upperBounds.x && mapBounds.z > cameraPosition.x + 0.5f * _screenWidth) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (mouseCoords.y < lowerBounds.y && mapBounds.w > cameraPosition.y + 0.5f * _screenHeight) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (mouseCoords.y > upperBounds.y && mapBounds.y < cameraPosition.y - 0.5f * _screenHeight) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}



	if (_inputManager.isKeyPressed(SDLK_ESCAPE)) {
		_interface.clearTargets();
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		_interface.updateBox(worldCoords);
	}
	else if (_interface.getBoxActive()) {
		bool append = _inputManager.isKeyPressed(SDLK_LSHIFT);
		_interface.updateTargets(_map, append);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		_interface.setTargetsDestination(_map, worldCoords);
	}


}

void Game::draw() {
	const unsigned int TEXTURE_UNIT = 0;
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint textureLocation = _colorProgram.getUniformLocation("tex");
	glUniform1i(textureLocation, TEXTURE_UNIT);

	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	_map.draw(_spriteBatch);
	_interface.draw(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D,  0);
	_colorProgram.unuse();

	_window.swapBuffer();
}

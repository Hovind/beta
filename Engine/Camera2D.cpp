#include "Camera2D.h"

namespace Engine {

	Camera2D::Camera2D(int screenWidth, int screenHeight)
	: _screenWidth(screenWidth)
	, _screenHeight(screenHeight)
	, _needsMatrixUpdate(true) 
	, _position(0.0f, 0.0f)
	, _cameraMatrix(1.0f)
	, _orthoMatrix(glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight)) {}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::updateResolution(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
		_needsMatrixUpdate = true;
	}

	//updates the camera matrix if needed
	void Camera2D::update() {

		//Only update if our position or scale have changed
		if (_needsMatrixUpdate) {
			
			//Camera Translation
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			
			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
		// Invert Y direction
		screenCoords.y = _screenHeight - screenCoords.y;
		// Make it so that 0 is the center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		// Translate with the camera position
		screenCoords += _position;
		return screenCoords;
	}
}
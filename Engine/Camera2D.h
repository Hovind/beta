#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    class Camera2D {
    public:
        Camera2D(int screenWidth, int screenHeight);
        ~Camera2D();
        
        void updateResolution(int screenWidth, int screenHeight);
        void update();

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

        void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
        
        glm::vec2 getPosition() { return _position; }
        glm::mat4 getCameraMatrix() { return _cameraMatrix; }

    private:
        int
            _screenWidth,
            _screenHeight;

        bool _needsMatrixUpdate;

        glm::vec2 _position;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
    };

}
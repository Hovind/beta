#pragma once

#include <string>
#include "GLTexture.h"

namespace Engine{
    class Sprite
    {
    public:
        Sprite(float x, float y, float width, float height, std::string filePath);
        ~Sprite();

        void init();

        void draw();
        
    private:
        float
        	_x,
    		_y,
    		_width,
    		_height;

        GLuint _vboID;
        GLTexture _texture;

    };
}
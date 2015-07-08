#include <cstddef>
#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

namespace Engine {
	const unsigned int
		QUAD = 6,
		RGBA = 4,
		COORD = 2,
		POSITION_INDEX = 0,
		COLOR_INDEX = 1,
		UV_INDEX = 2;



	Sprite::Sprite(float x, float y, float width, float height, std::string filePath)
	: _x(x)
	, _y(y)
	, _width(width)
	, _height(height)
	, _vboID(0) {
		_texture = ResourceManager::getTexture(filePath);
		init();
	}


	Sprite::~Sprite()
	{
		if (_vboID)
			glDeleteBuffers(1, &_vboID);
	}

	//Initializes the sprite VBO. x, y, width, and height are
	//in the normalized device coordinate space. so, [-1, 1]
	void Sprite::init() {
		if (!_vboID)
			glGenBuffers(1, &_vboID);

		Vertex vertexData[QUAD];

		//First Triangle
		vertexData[0].setPosition(_x + _width, _y + _height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(_x, _y + _height);
		vertexData[1].setUV(0, 1.0f);

		vertexData[2].setPosition(_x, _y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(_x, _y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(_x + _width, _y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5]. setPosition(_x + _width, _y + _height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (unsigned int i = 0; i < QUAD; ++i){
			vertexData[i].setColor(255, 255, 255, 255);
		}
		vertexData[1].setColor(0, 0, 255, 255);
		vertexData[4].setColor(255, 0, 0, 255);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void Sprite::draw() {
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		//bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(POSITION_INDEX);

		//Position attribute pointer
		glVertexAttribPointer(POSITION_INDEX, COORD, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		glVertexAttribPointer(COLOR_INDEX, RGBA, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		glVertexAttribPointer(UV_INDEX, COORD, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, QUAD);

		//Disable the vertex attrib array. This is not optional.
		glDisableVertexAttribArray(POSITION_INDEX);

		//Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
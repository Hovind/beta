#pragma once

#include <string>

#include "SpriteBatch.h"
#include "GLTexture.h"


class TileList {
public:
	TileList(glm::uvec2 mapSize);
	
	~TileList();

	unsigned int getLength();

	Engine::GLTexture &getTexture(unsigned int index);
	void setTexture(unsigned int index, std::string texturePath);

private:
	unsigned int _length;
	Engine::GLTexture *_textures;
};
#include "TileList.h"

#include "ResourceManager.h"

TileList::TileList(glm::uvec2 mapSize)
: _length(mapSize.x * mapSize.y)
, _textures(new Engine::GLTexture[_length]) {
	
}


TileList::~TileList() {

}

Engine::GLTexture &TileList::getTexture(unsigned int index) {
	return _textures[index];
}


void TileList::setTexture(unsigned int index, std::string texturePath) {
	_textures[index] = Engine::ResourceManager::getTexture(texturePath);
}
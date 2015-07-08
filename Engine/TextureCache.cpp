#include "TextureCache.h"
#include "ImageLoader.h"

namespace Engine {
	TextureCache::TextureCache() {

	}

	TextureCache::~TextureCache() {
		
	}

	GLTexture TextureCache::getTexture(std::string filePath) {
		std::map<std::string, GLTexture>::iterator mapIt = _textureMap.find(filePath);
		if (mapIt == _textureMap.end()){
			GLTexture texture = ImageLoader::loadPNG(filePath);
			_textureMap.insert(std::pair<std::string, GLTexture>(filePath, texture));
			return texture;
		}
		else
			return mapIt->second;
	}
}
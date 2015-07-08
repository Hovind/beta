#pragma once

#include <map>
#include <string>
#include "GLTexture.h"

namespace Engine{
	class TextureCache {
	public:
		TextureCache();
		~TextureCache();
		GLTexture getTexture(std::string filePath);
	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
#pragma once

#include <string>
#include "TextureCache.h"

namespace Engine {
	class ResourceManager {
	public:
		static GLTexture getTexture(std::string filePath);
	private:
		static TextureCache _textureCache;
	};
}
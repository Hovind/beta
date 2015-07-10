#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Exception.h"

namespace Engine {
	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {};

		std::vector<unsigned char> in;
		if (!IOManager::readFileToBuffer(filePath, in))
			throw Exception("Failed to read to buffer!");

		std::vector<unsigned char> out;
		unsigned long
			width,
			height;
		int error = decodePNG(out, width, height, &(in[0]), in.size());
		if (error)
			throw Exception("Failed to decode PNG!");

		texture.width = width;
		texture.height = height;

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
}

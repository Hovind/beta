#pragma once

#include <GL/glew.h>

namespace Engine {
	struct GLTexture {
		GLuint id;
		int
			width,
			height;
	};
}
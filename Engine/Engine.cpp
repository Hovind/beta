#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Engine {
	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);

    	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
}
#include "Window.h"
#include "MyException.h"

namespace Engine {
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	void Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

			SDL_DisplayMode displayMode;
			int videoDisplays = SDL_GetNumVideoDisplays();

			for (int i = 0; i < videoDisplays; ++i) {
				int error = SDL_GetCurrentDisplayMode(i, &displayMode);
				if (error)
					throw MyException("SDL could not get display mode!");

				_screenWidth = displayMode.w;
				_screenHeight = displayMode.h;
			}
		}
		else {
			_screenWidth = screenWidth;
			_screenHeight = screenHeight;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (!_sdlWindow) {
			throw MyException("SDL Window could not be created!");
		}
		
		

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (!glContext) {
			throw MyException("SDL_GL context could not be created!");
		}

		if (glewInit() != GLEW_OK) {
			throw MyException("Could not initialize glew!");
		}

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		SDL_GL_SetSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(_sdlWindow);
	}
}
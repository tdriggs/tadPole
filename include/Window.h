#ifndef WINDOW_H
#define WINDOW_H

#include "stdafx.h"

namespace tadPole
{
	#define WINDOW_CENTERED SDL_WINDOWPOS_CENTERED
	#define OPENGL_FLAGS SDL_WINDOW_OPENGL

	class Window
	{
	protected:
		SDL_Window * sdlWindow;

	public:
		Window(std::string name, int x, int y, int width, int height, int flags);
		~Window();
		
		HWND getWin32Handle();

	};
}

#endif

#include "stdafx.h"
#include "Window.h"

#include "SDL_syswm.h"

#include "Exception.h"

tadPole::Window::Window(std::string name, int x, int y, int width, int height, int flags)
{
	SDL_Init(SDL_INIT_VIDEO);

	this->sdlWindow = SDL_CreateWindow(name.c_str(), x, y, width, height, flags);

	if (this->sdlWindow == NULL)
	{
		EXCEPTION("Could not initialize window.");
	}
}

tadPole::Window::~Window()
{
	SDL_DestroyWindow(this->sdlWindow);
	SDL_Quit();
}

HWND tadPole::Window::getWin32Handle()
{
	SDL_SysWMinfo sdlinfo;
	SDL_version sdlver;
	SDL_VERSION(&sdlver);
	sdlinfo.version = sdlver;
	SDL_GetWindowWMInfo(this->sdlWindow, &sdlinfo);

	return sdlinfo.info.win.window;
}

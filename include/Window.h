#ifndef WINDOW_H
#define WINDOW_H

#include "stdafx.h"

namespace tadPole
{
	#define WINDOW_CENTERED SDL_WINDOWPOS_CENTERED
	#define OPENGL_FLAGS SDL_WINDOW_OPENGL

	/**
	* The actual window that is created by the operating system into which all other
	* displays can hook.
	*/
	class Window
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		SDL_Window * sdlWindow;	///< The SDL representation of this Window.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Window constructor.
		*/
		Window(
			std::string name,	///< The name of this Window.
			int x,				///< The x position of this Window on the screen in pixels.
			int y,				///< The y position of this Window on the screen in pixels.
			int width,			///< The width of this Window on the screen in pixels.
			int height,			///< The height of this Window on the screen in pixels.
			int flags			///< Any flags that apply to this Window.
		);

		/**
		* Window destructor.
		*/
		~Window();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Get the handle of this Window.
		*/
		HWND getWin32Handle();

	};
}

#endif

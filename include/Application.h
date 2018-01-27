#ifndef APPLICATION_H
#define APPLICATION_H

#include "stdafx.h"

#define SCREEN_WIDTH 1280	///< The height of the screen.
#define SCREEN_HEIGHT 720	///< The width of the screen.
#define FPS 60				///< The frames per second at which the display will be rendered.

namespace tadPole
{
	/**
	* An easy way to start up and shut down tadPole.
	*/
	class Application
	{
		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Application constructor.
		*/
		Application();

		/**
		* Application destructor.
		*/
		~Application();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Initialize this Application.
		*/
		void initialize(
			HWND windowHandle	///< The handle of the operating system window in which tadPole will display.
		);

		/**
		* Update tadPole.
		*/
		void update(
			float deltaTime	///< The time that has passed since the last frame in seconds.
		);

		/**
		* Render tadPole.
		*/
		void render();
	};
}

#endif

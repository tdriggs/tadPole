#include "stdafx.h"

#include "Keyboard.h"
#include "Event.h"
#include "Window.h"

#include "Application.h"
#include "LogManager.h"
#include "InputManager.h"

int main(int argc, char * argv[])
{
	tadPole::Window * window = new tadPole::Window("tadPole", WINDOW_CENTERED, WINDOW_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, OPENGL_FLAGS);

	tadPole::Application * app = new tadPole::Application();
	app->initialize(window->getWin32Handle());

	unsigned int prevTimeMS = 0;
	unsigned int deltaTimeMS = 0;
	const float frameTime = 1000.0f / FPS;
	unsigned int frameTimer = frameTime + 1;

	tadPole::Event event;
	bool gameOver = false;
	while (!gameOver) 
	{
		// Update Time Variables
		unsigned int ticks = SDL_GetTicks();
		deltaTimeMS = ticks - prevTimeMS;
		prevTimeMS = ticks;

		frameTimer += deltaTimeMS;

		// Handle Events
		while (event.poll())
		{
			if (event.getType() == EVT_QUIT)
			{
				gameOver = 1;
			}
			if (event.getType() == EVT_KEYDOWN)
			{
				INPUT_MANAGER->key_down(event.getKey());
			}
			if (event.getType() == EVT_KEYDOWN)
			{
				INPUT_MANAGER->key_up(event.getKey());
			}
		}

		// Framerate Control
		if (frameTimer >= frameTime)
		{
			// Update
			app->update(frameTimer / 1000.0f);

			// Render
			app->render();

			frameTimer = 0.0;
		}
	}

	return 0;
}

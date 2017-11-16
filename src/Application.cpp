#include "stdafx.h"
#include "Application.h"

#include "Exception.h"

tadPole::Application::Application() { }

tadPole::Application::~Application() { }

void tadPole::Application::initialize(HWND windowHandle)
{
	try
	{
		RenderManager * renderManager = new RenderManager(windowHandle);
		LogManager * logManager = new LogManager();
		DebugOverlay * debugOverlay = new DebugOverlay();
		InputManager * inputManager = new InputManager();
		GameObjectManager * gameObjectManager = new GameObjectManager();

		RENDER_MANAGER->initializeBaseScene();

		LOG_MANAGER->log("Initialized Successfully!");
	}
	catch (Exception e) {
		if (LOG_MANAGER)
		{
			e.logException();
		}
	}
}

void tadPole::Application::update(float deltaTime)
{
	DEBUG_OVERLAY->update(deltaTime);
	RENDER_MANAGER->update(deltaTime);
}

void tadPole::Application::render()
{
	RENDER_MANAGER->render();
}

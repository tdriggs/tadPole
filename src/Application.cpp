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

		LOG_MANAGER->log("Initialized Successfully!");

		Scene * scene = new Scene("lv01.json");
		scene->load();
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
	try
	{
		DEBUG_OVERLAY->update(deltaTime);
	}
	catch (Exception e) {
		if (LOG_MANAGER)
		{
			e.logException();
		}
	}
}

void tadPole::Application::render()
{
	try
	{
		RENDER_MANAGER->render();
	}
	catch (Exception e) {
		if (LOG_MANAGER)
		{
			e.logException();
		}
	}
}

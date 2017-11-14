#include "stdafx.h"
#include "Application.h"

#include "Exception.h"

using namespace tadPole;

Application::Application() : Singleton<Application>()
{
}

Application::~Application()
{
}

void Application::initialize_win32(HWND hWnd)
{
	std::string windowHandle = std::to_string((size_t)hWnd);
	WindowParams windowParams;
	windowParams["externalWindowHandle"] = windowHandle;

	this->initialize_common(windowParams);
}

void Application::initialize_common(WindowParams & windowParams)
{
	try
	{
		this->renderManager = new RenderManager(windowParams);
		this->logManager = new LogManager();
		this->debugOverlay = new DebugOverlay();
		this->inputManager = new InputManager();
		this->gameObjectManager = new GameObjectManager();

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

void Application::update(float deltaTime)
{
	DEBUG_OVERLAY->update(deltaTime);
	RENDER_MANAGER->update(deltaTime);
}

void Application::render()
{
	RENDER_MANAGER->render();
}

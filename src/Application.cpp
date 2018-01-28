#include "stdafx.h"
#include "Application.h"

#include "Exception.h"
#include "RenderManager.h"
#include "LogManager.h"
#include "DebugOverlay.h"
#include "InputManager.h"
#include "PythonScriptManager.h"
#include "Scene.h"

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
		PythonScriptManager * pythonScriptManager = new PythonScriptManager();
		Scene * scene = new Scene();

		LOG_MANAGER->log("Initialized Successfully!");

		PYTHON_SCRIPT_MANAGER->executeScript("init.py");
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

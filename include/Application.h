#ifndef TADPOLE_APPLICATION_H
#define TADPOLE_APPLICATION_H

#include "stdafx.h"

#include "Singleton.h"
#include "RenderManager.h"
#include "LogManager.h"
#include "DebugOverlay.h"
#include "InputManager.h"
#include "GameObjectManager.h"

#define APPLICATION Application::getInstance()
#define SCREEN_WIDTH 1280  // Maintain a 16:9 aspect ratio
#define SCREEN_HEIGHT 720
#define FPS 60
typedef Ogre::NameValuePairList WindowParams;

namespace tadPole
{
	class Application : public Singleton<Application>
	{
	public:
		Application();
		~Application();

		#ifdef _WIN32
		void initialize_win32(HWND hWnd);
		#endif

		void update(float deltaTime);
		void render();

	protected:
		DebugOverlay * debugOverlay;
		LogManager * logManager;
		InputManager * inputManager;
		RenderManager * renderManager;
		GameObjectManager * gameObjectManager;

		void initialize_common(WindowParams & windowParams);
	};
}

#endif

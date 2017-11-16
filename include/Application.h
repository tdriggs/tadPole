#ifndef TADPOLE_APPLICATION_H
#define TADPOLE_APPLICATION_H

#include "stdafx.h"

#include "RenderManager.h"
#include "LogManager.h"
#include "DebugOverlay.h"
#include "InputManager.h"
#include "GameObjectManager.h"

#define SCREEN_WIDTH 1280  // Maintain a 16:9 aspect ratio
#define SCREEN_HEIGHT 720
#define FPS 60

namespace tadPole
{
	class Application
	{
	public:
		Application();
		~Application();

		void update(float deltaTime);
		void render();
		void initialize(HWND windowHandle);
	};
}

#endif

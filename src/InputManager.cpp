#include "stdafx.h"
#include "InputManager.h"

#include "LogManager.h"
#include "DebugOverlay.h"

tadPole::InputManager::InputManager() : Singleton<InputManager>() { }

tadPole::InputManager::~InputManager() { }

void tadPole::InputManager::key_down(Key key)
{
	LOG_MANAGER->log("KEY PRESS: " + std::to_string(key));
	if (key == KEY_F11)
	{
		DEBUG_OVERLAY->toggleVisible();
	}
}

void tadPole::InputManager::key_up(Key key)
{

}

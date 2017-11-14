#include "stdafx.h"
#include "InputManager.h"

#include "LogManager.h"
#include "DebugOverlay.h"
#include "GameObjectManager.h"

using namespace tadPole;

InputManager::InputManager() : Singleton<InputManager>()
{
}

InputManager::~InputManager()
{
}

void InputManager::key_down(Key key)
{
	if (key == KEY_F11)
	{
		DEBUG_OVERLAY->toggleVisible();
	}
	if (key == KEY_C)
	{
		GAME_OBJECT_MANAGER->getGameObject("rotaters/orbiter")->setParent(GAME_OBJECT_MANAGER->getGameObject("rotaters/central/orbiterBase"));
	}
	if (key == KEY_L)
	{
		GAME_OBJECT_MANAGER->getGameObject("rotaters/orbiter")->setParent(GAME_OBJECT_MANAGER->getGameObject("rotaters/left/orbiterBase"));
	}
	if (key == KEY_H)
	{
		GAME_OBJECT_MANAGER->setGroupActive("bullets", false);
	}
	if (key == KEY_S)
	{
		GAME_OBJECT_MANAGER->setGroupActive("bullets", true);
	}
	if (key == KEY_D)
	{
		GAME_OBJECT_MANAGER->deleteGroup("bullets");
		GAME_OBJECT_MANAGER->createGroup("bullets");
	}

	LOG_MANAGER->log("KEY PRESS: " + std::to_string(key));
}

void InputManager::key_up(Key key)
{
	//LOG_MANAGER->log("KEY UP: " + KEY_NAMES.at(key));
}

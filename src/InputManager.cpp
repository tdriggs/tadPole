#include "stdafx.h"
#include "InputManager.h"

#include "LogManager.h"
#include "DebugOverlay.h"
#include "GameObjectManager.h"

tadPole::InputManager::InputManager() : Singleton<InputManager>() { }

tadPole::InputManager::~InputManager() { }

void tadPole::InputManager::key_down(Key key)
{
	if (key == KEY_F11)
	{
		DEBUG_OVERLAY->toggleVisible();
	}
	if (key == KEY_C)
	{
		GAME_OBJECT_MANAGER->getGameObject("orbiter")->setParent(GAME_OBJECT_MANAGER->getGameObject("centralOrbiterBase"));
	}
	if (key == KEY_L)
	{
		GAME_OBJECT_MANAGER->getGameObject("orbiter")->setParent(GAME_OBJECT_MANAGER->getGameObject("leftOrbiterBase"));
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

void tadPole::InputManager::key_up(Key key)
{

}

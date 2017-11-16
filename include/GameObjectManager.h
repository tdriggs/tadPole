#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "stdafx.h"
#include "Singleton.h"

#include "GameObject.h"

#define GAME_OBJECT_MANAGER tadPole::GameObjectManager::getInstance()
#define NO_GROUP_NAME "No Group"

namespace tadPole
{
	class GameObjectManager : public Singleton<GameObjectManager>
	{
	protected:
		std::map<std::string, std::vector<GameObject *>> components;

	public:
		 GameObjectManager();
		 ~GameObjectManager();

		 void createGroup(std::string group);
		 void setGroupActive(std::string group, bool active);
		 void deleteGroup(std::string group);
		 GameObject * getGameObject(std::string name);
		 GameObject * createGameObject(std::string name);
		 GameObject * createGameObject(std::string group, std::string name);
		 std::vector<GameObject *> getGroup(std::string group);
	};
}

#endif

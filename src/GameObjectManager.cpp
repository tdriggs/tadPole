#include "stdafx.h"
#include "GameObjectManager.h"

#include "Exception.h"

tadPole::GameObjectManager::GameObjectManager() : Singleton<GameObjectManager>()
{
	this->components = std::map<std::string, std::vector<GameObject *>>();
	this->components[NO_GROUP_NAME] = std::vector<GameObject *>();
}

tadPole::GameObjectManager::~GameObjectManager()
{
	std::map<std::string, std::vector<GameObject *>>::iterator map_it;
	for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
	{
		std::vector<GameObject *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			delete *vector_it;
		}
	}
}

void tadPole::GameObjectManager::createGroup(std::string group)
{
	if (this->components.find(group) != this->components.end())
	{
		EXCEPTION("Group already exists: " + group);
	}

	this->components[group] = std::vector<GameObject *>();
}

void tadPole::GameObjectManager::setGroupActive(std::string group, bool active)
{
	if (this->components.find(group) == this->components.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	std::vector<GameObject *> gameObjects = this->components[group];
	std::vector<GameObject *>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->setActive(active);
	}
}

void tadPole::GameObjectManager::deleteGroup(std::string group)
{
	if (this->components.find(group) == this->components.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	std::vector<GameObject *> gameObjects = this->components[group];
	std::vector<GameObject *>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		delete *it;
	}

	this->components.erase(group);
}

tadPole::GameObject * tadPole::GameObjectManager::getGameObject(std::string name)
{
	std::map<std::string, std::vector<GameObject *>>::iterator map_it;
	for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
	{
		std::vector<GameObject *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			GameObject * go = (GameObject *)(*vector_it);
			if (std::strcmp(go->name.c_str(), name.c_str()) == 0)
			{
				return go;
			}
		}
	};

	EXCEPTION("GameObject does not exist: " + name);
}

tadPole::GameObject * tadPole::GameObjectManager::createGameObject(std::string name)
{
	GameObject * go = new GameObject(name);
	this->components[NO_GROUP_NAME].push_back(go);

	return go;
}

tadPole::GameObject * tadPole::GameObjectManager::createGameObject(std::string group, std::string name)
{
	if (this->components.find(group) == this->components.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	GameObject * go = new GameObject(name);
	this->components[group].push_back(go);
	
	return go;
}

std::vector<tadPole::GameObject*> tadPole::GameObjectManager::getGroup(std::string group)
{
	if (this->components.find(group) == this->components.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	return this->components[group];
}

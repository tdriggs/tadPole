#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"

#include "Serializable.h"
#include "Singleton.h"
#include "GameObject.h"

#define NO_GROUP_NAME "No Group"

namespace tadPole
{
	class Scene : Serializable
	{
	protected:
		std::string fileName;
		GameObject * rootObject;
		std::map<std::string, std::vector<GameObject *>> objects;

	public:
		Scene(std::string fileName);
		 ~Scene();

		 void save();
		 void load();
		 void clear();
		 std::string serialize();

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

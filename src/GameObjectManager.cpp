#include "stdafx.h"
#include "GameObjectManager.h"

#include "Exception.h"

tadPole::GameObjectManager::GOMTreeNode::GOMTreeNode(GOMTreeNode * parent)
{
	this->parent = parent;
	this->data = nullptr;
	this->children = std::map<std::string, GOMTreeNode *>();
	if (parent != nullptr)
	{
		this->active = parent->active;
	}
	else
	{
		this->active = true;
	}
}

tadPole::GameObjectManager::GOMTreeNode::~GOMTreeNode()
{
	std::map<std::string, GOMTreeNode *>::iterator map_it;
	for (map_it = this->children.begin(); map_it != this->children.end(); ++map_it)
	{
		delete map_it->second;
	}

	delete this->data;
}

std::pair<std::string, std::string> tadPole::GameObjectManager::GOMTreeNode::splitName(std::string name)
{
	std::string first = name.substr(0, name.find('/'));
	std::string second = "";
	if (name.find('/') != std::string::npos)
	{
		second = name.substr(name.find('/') + 1, name.length());
	}
	return std::pair<std::string, std::string>(first, second);
}

void tadPole::GameObjectManager::GOMTreeNode::addNode(std::string namePath)
{
	std::pair<std::string, std::string> nameParts = this->splitName(namePath);

	if (nameParts.second.length() != 0)
	{
		if (this->children.find(nameParts.first) == this->children.end())
		{
			EXCEPTION("Create base group first: " + namePath);
			// Uncomment if I don't want to require that base groups are created first.
			// this->children[nameParts.first] = new GOMTreeNode(this);
		}

		this->children[nameParts.first]->addNode(nameParts.second);
	}
	else
	{
		if (this->children.find(nameParts.first) != this->children.end())
		{
			EXCEPTION("Cannot create GameObjects with the same name: " + namePath);
		}

		this->children[nameParts.first] = new GOMTreeNode(this);
	}
}

tadPole::GameObjectManager::GOMTreeNode * tadPole::GameObjectManager::GOMTreeNode::getNode(std::string namePath)
{
	std::pair<std::string, std::string> nameParts = this->splitName(namePath);

	if (this->children.find(nameParts.first) == this->children.end())
	{
		EXCEPTION("No such group: " + namePath);
		// Uncomment this if I don't want to require that the group be created to retrieve this node.
		// this->children[nameParts.first] = new GOMTreeNode(this);
	}

	if (nameParts.second.length() == 0)
	{
		return this->children[nameParts.first];
	}
	else
	{
		return this->children[nameParts.first]->getNode(nameParts.second);
	}
}

std::vector<tadPole::GameObject *> tadPole::GameObjectManager::GOMTreeNode::getObjectsInGroup()
{
	std::vector<tadPole::GameObject *> gameObjectsInGroup = std::vector<tadPole::GameObject *>();
	std::vector<tadPole::GameObjectManager::GOMTreeNode *> nodesToSearch = std::vector<tadPole::GameObjectManager::GOMTreeNode *>();
	nodesToSearch.push_back(this);

	while (nodesToSearch.size() > 0)
	{
		tadPole::GameObjectManager::GOMTreeNode * node = nodesToSearch.front();
		nodesToSearch.erase(nodesToSearch.begin());

		std::map<std::string, tadPole::GameObjectManager::GOMTreeNode *>::iterator map_it;
		for (map_it = node->children.begin(); map_it != node->children.end(); ++map_it)
		{
			if (map_it->second->data != nullptr)
			{
				gameObjectsInGroup.push_back(map_it->second->data);
			}

			nodesToSearch.push_back(map_it->second);
		}
	}

	return gameObjectsInGroup;
}

void tadPole::GameObjectManager::GOMTreeNode::setGroupActive(bool active)
{
	std::vector<tadPole::GameObjectManager::GOMTreeNode *> nodesToSearch = std::vector<tadPole::GameObjectManager::GOMTreeNode *>();
	nodesToSearch.push_back(this);

	while (nodesToSearch.size() > 0)
	{
		tadPole::GameObjectManager::GOMTreeNode * node = nodesToSearch.front();
		nodesToSearch.erase(nodesToSearch.begin());

		node->active = active;

		std::map<std::string, tadPole::GameObjectManager::GOMTreeNode *>::iterator map_it;
		for (map_it = node->children.begin(); map_it != node->children.end(); ++map_it)
		{
			nodesToSearch.push_back(map_it->second);
		}
	}
}

tadPole::GameObjectManager::GameObjectManager() : Singleton<GameObjectManager>()
{
	this->rootNode = new GOMTreeNode(nullptr);
}

tadPole::GameObjectManager::~GameObjectManager()
{
	delete this->rootNode;
}

void tadPole::GameObjectManager::createGroup(std::string groupPath)
{
	this->rootNode->addNode(groupPath);
}

void tadPole::GameObjectManager::setGroupActive(std::string groupPath, bool active)
{
	this->rootNode->getNode(groupPath)->setGroupActive(active);
	std::vector<GameObject *> gameObjects = this->rootNode->getNode(groupPath)->getObjectsInGroup();
	std::vector<GameObject *>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->setActive(active);
	}
}

void tadPole::GameObjectManager::deleteGroup(std::string groupPath)
{
	GOMTreeNode * node = this->rootNode->getNode(groupPath);

	if (node->parent == nullptr)
	{
		EXCEPTION("Cannot delete root group: " + groupPath);
	}

	std::string nameKey = groupPath;
	if (nameKey.find('/') != std::string::npos)
	{
		nameKey = nameKey.substr(nameKey.find('/') + 1, nameKey.length());
	}

	GOMTreeNode * parent = node->parent;
	delete node;
	parent->children.erase(nameKey);
}

tadPole::GameObject * tadPole::GameObjectManager::getGameObject(std::string namePath)
{
	GOMTreeNode * node = this->rootNode->getNode(namePath);

	if (node->data == nullptr)
	{
		EXCEPTION("GameObject does not exist: " + namePath);
	}

	return node->data;
}

tadPole::GameObject * tadPole::GameObjectManager::createGameObject(std::string namePath)
{
	GOMTreeNode * node = this->rootNode->getNode(namePath);

	if (node->data != nullptr)
	{
		EXCEPTION("Cannot create GameObjects with the same name: " + namePath);
	}

	node->data = new GameObject(namePath);
	node->data->setActive(node->active);
	return node->data;
}

std::vector<tadPole::GameObject*> tadPole::GameObjectManager::getGroup(std::string groupPath)
{
	return this->rootNode->getNode(groupPath)->getObjectsInGroup();
}

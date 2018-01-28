#include "stdafx.h"
#include "Scene.h"

#include "LogManager.h"
#include "Exception.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "RenderManager.h"

tadPole::Scene::Scene()
{
	this->rootObject = new GameObject("ROOT");
	this->objects = std::map<std::string, std::vector<GameObject *>>();
	this->objects[NO_GROUP_NAME] = std::vector<GameObject *>();
}

tadPole::Scene::~Scene()
{
	for (std::map<std::string, std::vector<GameObject *>>::iterator map_it = this->objects.begin(); map_it != this->objects.end(); ++map_it)
	{
		for (std::vector<GameObject *>::iterator vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			delete * vector_it;
		}
	}
	this->objects.clear();
}

std::string tadPole::Scene::serialize()
{
	std::ostringstream result;
	std::ostringstream groupString;
	std::string groupSeperator = "";
	std::map<std::string, std::vector<GameObject *>>::iterator map_it;
	for (map_it = this->objects.begin(); map_it != this->objects.end(); ++map_it)
	{
		std::ostringstream gameObjectString;
		std::string objectSeperator = "";
		std::vector<GameObject *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			GameObject * gameObject = ((GameObject *)(*vector_it));
			std::string gameObjectJson = gameObject->serialize();
			gameObjectString << objectSeperator << gameObjectJson;
			objectSeperator = ",";
		}

		groupString << groupSeperator << "{\n\t\t\t\"groupName\": \"" << map_it->first << "\", \n\t\t\t\"gameObjects\": [\n\t\t\t\t" << gameObjectString.str() << "\n\t\t\t]\n\t\t}";
		groupSeperator = ",";
	}

	result << "{\n\t\"groups\": [\n\t\t" << groupString.str() << "\n\t]\n}";

	return result.str();
}

void tadPole::Scene::save(std::string fileName)
{
	std::string jsonString = this->serialize();
	std::ofstream file;
	file.open(fileName);
	file << jsonString;
	file.flush();
	file.close();

	LOG_MANAGER->log("Scene Saved to File: " + fileName);
}

void tadPole::Scene::load(std::string fileName)
{
	this->clear();

	rapidjson::Document document;
	std::ifstream file;
	std::ostringstream fileText;
	std::string tempString;
	file.open(fileName);
	while (!file.eof())
	{
		std::getline(file, tempString);
		fileText << tempString;
	}
	file.close();
	document.Parse(fileText.str().c_str());

	std::map<GameObject *, std::string> parents = std::map<GameObject *, std::string>();
	rapidjson::Value groups = document["groups"].GetArray();
	for (rapidjson::Value::ConstValueIterator group_it = groups.Begin(); group_it != groups.End(); ++group_it)
	{
		std::string groupName = (*group_it)["groupName"].GetString();
		if (groupName != "No Group")
		{
			this->createGroup(groupName);
		}

		const rapidjson::Value & gameObjects = (*group_it)["gameObjects"];
		for (rapidjson::Value::ConstValueIterator gameObject_it = gameObjects.Begin(); gameObject_it != gameObjects.End(); ++gameObject_it)
		{
			std::string name = (*gameObject_it)["name"].GetString();
			std::string parentName = (*gameObject_it)["parentName"].GetString();
			bool active = (*gameObject_it)["active"].GetBool();
			const rapidjson::Value & worldPositionArray = (*gameObject_it)["worldPosition"];
			const rapidjson::Value & worldOrientationArray = (*gameObject_it)["worldOrientation"];
			const rapidjson::Value & worldScaleArray = (*gameObject_it)["worldScale"];
			glm::vec3 worldPosition(worldPositionArray[0].GetFloat(), worldPositionArray[1].GetFloat(), worldPositionArray[2].GetFloat());
			glm::vec3 worldOrientationAxis(worldOrientationArray[0].GetFloat(), worldOrientationArray[1].GetFloat(), worldOrientationArray[2].GetFloat());
			float worldOrientationAngle = worldOrientationArray[3].GetFloat();
			glm::vec3 worldScale(worldScaleArray[0].GetFloat(), worldScaleArray[1].GetFloat(), worldScaleArray[2].GetFloat());

			GameObject * gameObject = this->createGameObject(groupName, name);
			gameObject->active = active;
			gameObject->setPosition(worldPosition);
			gameObject->setOrientation(worldOrientationAxis, worldOrientationAngle);
			gameObject->setScale(worldScale);

			const rapidjson::Value & components = (*gameObject_it)["components"];
			for (rapidjson::Value::ConstValueIterator component_it = components.Begin(); component_it != components.End(); ++component_it)
			{
				std::string type = (*component_it)["type"].GetString();
				if (type == "MESH")
				{
					std::string fileName = (*component_it)["fileName"].GetString();
					MeshComponent * meshComponent = gameObject->createMeshComponent(fileName);
				}
				else if (type == "CAMERA")
				{
					const rapidjson::Value & directionArray = (*component_it)["direction"];
					glm::vec3 direction(directionArray[0].GetFloat(), directionArray[1].GetFloat(), directionArray[2].GetFloat());
					float nearClipDistance = (*component_it)["nearClipDistance"].GetFloat();
					float farClipDistance = (*component_it)["farClipDistance"].GetFloat();
					std::string viewport = (*component_it)["viewport"].GetString();

					CameraComponent * cameraComponent = gameObject->createCameraComponent();
					cameraComponent->setDirection(direction);
					cameraComponent->setClipDistances(nearClipDistance, farClipDistance);
					cameraComponent->setViewport(viewport);
				}
				else if (type == "LIGHT")
				{
					std::string lightTypeString = (*component_it)["lightType"].GetString();
					LightType lightType = (lightTypeString == "DIRECTIONAL") ? LightType::DIRECTIONAL : ((lightTypeString == "POINT") ? LightType::POINT : LightType::SPOT);
					const rapidjson::Value & directionArray = (*component_it)["direction"];
					const rapidjson::Value & diffuseArray = (*component_it)["diffuseColor"];
					const rapidjson::Value & specularArray = (*component_it)["specularColor"];
					glm::vec3 direction(directionArray[0].GetFloat(), directionArray[1].GetFloat(), directionArray[2].GetFloat());
					glm::vec3 diffuseColor(diffuseArray[0].GetFloat(), diffuseArray[1].GetFloat(), diffuseArray[2].GetFloat());
					glm::vec3 specularColor(specularArray[0].GetFloat(), specularArray[1].GetFloat(), specularArray[2].GetFloat());
					float spotlightInnerAngle = (*component_it)["spotlightInnerAngle"].GetFloat();
					float spotlightOuterAngle = (*component_it)["spotlightOuterAngle"].GetFloat();

					LightComponent * lightComponent = gameObject->createLightComponent(lightType);
					lightComponent->setDirection(direction);
					lightComponent->setDiffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b);
					lightComponent->setSpecularColor(specularColor.r, specularColor.g, specularColor.b);
					lightComponent->setSpotlightAngles(spotlightInnerAngle, spotlightOuterAngle);
				}
			}

			if (parentName != "ROOT")
			{
				parents.insert(std::pair<GameObject *, std::string>(gameObject, parentName));
			}
		}
	}

	for (std::map<GameObject *, std::string>::iterator map_it = parents.begin(); map_it != parents.end(); ++map_it)
	{
		map_it->first->setParentInPlace(this->getGameObject(map_it->second));
	}

	LOG_MANAGER->log("File Loaded: " + fileName);
}

void tadPole::Scene::clear()
{
	std::vector<std::string> groups = std::vector<std::string>();
	for (std::map<std::string, std::vector<GameObject *>>::iterator map_it = this->objects.begin(); map_it != this->objects.end(); ++map_it)
	{
		if (map_it->first != "SCENEVIEW")
		{
			for (std::vector<GameObject *>::iterator vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
			{
				delete * vector_it;
			}
			groups.push_back(map_it->first);
		}
	}

	for (std::vector<std::string>::iterator vector_it = groups.begin(); vector_it != groups.end(); ++vector_it)
	{
		this->objects.erase(*vector_it);
	}

	this->objects[NO_GROUP_NAME] = std::vector<GameObject *>();
}

void tadPole::Scene::createGroup(std::string group)
{
	if (this->objects.find(group) != this->objects.end())
	{
		EXCEPTION("Group already exists: " + group);
	}

	this->objects[group] = std::vector<GameObject *>();
}

void tadPole::Scene::deleteGroup(std::string group)
{
	if (this->objects.find(group) == this->objects.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	std::vector<GameObject *> gameObjects = this->objects[group];
	std::vector<GameObject *>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		delete *it;
	}

	this->objects.erase(group);
}

void tadPole::Scene::setGroupActive(std::string group, bool active)
{
	if (this->objects.find(group) == this->objects.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	std::vector<GameObject *> gameObjects = this->objects[group];
	std::vector<GameObject *>::iterator it;
	for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->setActive(active);
	}
}

tadPole::GameObject * tadPole::Scene::createGameObject(std::string name)
{
	GameObject * go = new GameObject(this->rootObject, name);
	this->objects[NO_GROUP_NAME].push_back(go);

	return go;
}

tadPole::GameObject * tadPole::Scene::createGameObject(std::string group, std::string name)
{
	if (this->objects.find(group) == this->objects.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	GameObject * go = new GameObject(this->rootObject, name);
	this->objects[group].push_back(go);
	
	return go;
}

void tadPole::Scene::deleteGameObject(std::string name)
{
	std::map<std::string, std::vector<GameObject *>>::iterator map_it;
	for (map_it = this->objects.begin(); map_it != this->objects.end(); ++map_it)
	{
		std::vector<GameObject *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			GameObject * go = (GameObject *)(*vector_it);
			if (std::strcmp(go->name.c_str(), name.c_str()) == 0)
			{
				map_it->second.erase(vector_it);
				delete go;
				break;
			}
		}
	}
}

std::vector<tadPole::GameObject*> tadPole::Scene::getGroup(std::string group)
{
	if (this->objects.find(group) == this->objects.end())
	{
		EXCEPTION("Group does not exist: " + group);
	}

	return this->objects[group];
}

tadPole::GameObject * tadPole::Scene::getGameObject(std::string name)
{
	std::map<std::string, std::vector<GameObject *>>::iterator map_it;
	for (map_it = this->objects.begin(); map_it != this->objects.end(); ++map_it)
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

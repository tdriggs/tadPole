#include "stdafx.h"
#include "GameObject.h"

#include "Exception.h"
#include "Scene.h"
#include "RenderManager.h"
#include "Component.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "PythonScriptComponent.h"

tadPole::GameObject::GameObject(std::string name)
{
	this->name = name;
	this->active = true;
	this->children = std::vector<GameObject *>();
	this->components = std::map<tadPole::ComponentType, std::vector<Component *>>();

	this->parentObject = NULL;
	this->sceneNode = RENDER_MANAGER->sceneManager->getRootSceneNode();
}

tadPole::GameObject::GameObject(GameObject * rootObject, std::string name)
{
	this->name = name;
	this->active = true;
	this->children = std::vector<GameObject *>();
	this->components = std::map<tadPole::ComponentType, std::vector<Component *>>();

	this->parentObject = rootObject;
	this->sceneNode = this->parentObject->sceneNode->createChildSceneNode();
}

tadPole::GameObject::~GameObject()
{
	std::map<tadPole::ComponentType, std::vector<Component *>>::iterator map_it;
	for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
	{
		std::vector<Component *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			delete *vector_it;
		}
		map_it->second.clear();
	}
	this->components.clear();

	for (std::vector<GameObject *>::iterator it = this->children.begin(); it < this->children.end(); ++it)
	{
		(*it)->parentObject = SCENE->rootObject;
	}

	if (this->sceneNode != NULL)
	{
		if (this->parentObject != NULL)
		{
			this->parentObject->sceneNode->removeChild(this->sceneNode);
		}
		this->sceneNode->detachAllObjects();
		RENDER_MANAGER->sceneManager->destroySceneNode(this->sceneNode);
	}
}

std::string tadPole::GameObject::serialize()
{
	std::ostringstream result;

	if (this->parentObject != NULL)
	{
		glm::vec3 worldPosition = this->getWorldPosition();
		glm::quat worldOrientation = this->getWorldOrientation();
		glm::vec3 worldScale = this->getWorldScale();
		std::ostringstream worldPositionString;
		std::ostringstream worldOrientationString;
		std::ostringstream worldScaleString;
		worldPositionString << "[" << worldPosition.x << ", " << worldPosition.y << ", " << worldPosition.z << "]";
		worldOrientationString << "[" << worldOrientation.x << ", " << worldOrientation.y << ", " << worldOrientation.z << ", " << worldOrientation.w << "]";
		worldScaleString << "[" << worldScale.x << ", " << worldScale.y << ", " << worldScale.z << "]";

		std::string seperator = "";
		std::ostringstream componentString;
		std::map<tadPole::ComponentType, std::vector<Component *>>::iterator map_it;
		for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
		{
			std::vector<Component *>::iterator vector_it;
			for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
			{
				Component * component = ((Component *)(*vector_it));
				std::string componentJson = component->serialize();
				componentString << seperator << componentJson.c_str();
				seperator = ",";
			}
		}

		result << "{\n\t\t\t\t\t\"name\": \"" << this->name << "\",\n\t\t\t\t\t\"parentName\": \"" << this->parentObject->name << "\",\n\t\t\t\t\t\"active\": " << (this->active ? "true" : "false")
			<< ",\n\t\t\t\t\t\"worldPosition\": " << worldPositionString.str() << ",\n\t\t\t\t\t\"worldOrientation\": " << worldOrientationString.str()
			<< ",\n\t\t\t\t\t\"worldScale\": " << worldScaleString.str() << ",\n\t\t\t\t\t\"components\": [\n\t\t\t\t\t\t" << componentString.str() << "\n\t\t\t\t\t]\n\t\t\t\t}";
	}

	return result.str();
}

void tadPole::GameObject::update(float deltaTime)
{
	std::map<tadPole::ComponentType, std::vector<Component *>>::iterator map_it;
	for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
	{
		std::vector<Component *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			((Component *)(*vector_it))->update(deltaTime);
		}
	}
}

tadPole::MeshComponent * tadPole::GameObject::createMeshComponent(std::string fileName)
{
	MeshComponent * meshComponent = new MeshComponent(this, fileName);
	this->components[ComponentType::MESH].push_back(meshComponent);
	this->sceneNode->attachObject(meshComponent->entity);
	meshComponent->setActive(this->active);

	return meshComponent;
}

tadPole::CameraComponent * tadPole::GameObject::createCameraComponent()
{
	CameraComponent * cameraComponent = new CameraComponent(this);
	this->components[ComponentType::CAMERA].push_back(cameraComponent);
	this->sceneNode->attachObject(cameraComponent->camera);
	cameraComponent->setActive(this->active);

	return cameraComponent;
}

tadPole::LightComponent * tadPole::GameObject::createLightComponent(LightType type)
{
	LightComponent * lightComponent = new LightComponent(this, type);
	this->components[ComponentType::LIGHT].push_back(lightComponent);
	this->sceneNode->attachObject(lightComponent->light);
	lightComponent->setActive(this->active);

	return lightComponent;
}

tadPole::PythonScriptComponent * tadPole::GameObject::createPythonScriptComponent(std::string scriptName)
{
	PythonScriptComponent * scriptComponent = new PythonScriptComponent(this, scriptName);
	this->components[ComponentType::SCRIPT].push_back(scriptComponent);
	scriptComponent->setActive(this->active);

	return scriptComponent;
}

std::string tadPole::GameObject::getName()
{
	return this->name;
}

int tadPole::GameObject::getComponentCount(ComponentType type)
{
	return this->components[type].size();
}

tadPole::PyTadPole_GameObject * tadPole::GameObject::getPyObject()
{
	return this->pythonGameObject;
}

glm::vec3 tadPole::GameObject::getLocalPosition()
{
	Ogre::Vector3 position = this->sceneNode->getPosition();
	return glm::vec3(position.x, position.y, position.z);
}

glm::vec3 tadPole::GameObject::getWorldPosition()
{
	Ogre::Vector3 position = this->sceneNode->_getDerivedPosition();
	return glm::vec3(position.x, position.y, position.z);
}

glm::quat tadPole::GameObject::getLocalOrientation()
{
	Ogre::Quaternion orientation = this->sceneNode->getOrientation();
	return glm::quat(orientation.x, orientation.y, orientation.z, orientation.w);
}

glm::quat tadPole::GameObject::getWorldOrientation()
{
	Ogre::Quaternion orientation = this->sceneNode->_getDerivedOrientation();
	return glm::quat(orientation.x, orientation.y, orientation.z, orientation.w);
}

glm::vec3 tadPole::GameObject::getLocalScale()
{
	Ogre::Vector3 scale = this->sceneNode->getScale();
	return glm::vec3(scale.x, scale.y, scale.z);
}

glm::vec3 tadPole::GameObject::getWorldScale()
{
	Ogre::Vector3 scale = this->sceneNode->_getDerivedScale();
	return glm::vec3(scale.x, scale.y, scale.z);
}

void tadPole::GameObject::setActive(bool active)
{
	this->active = active;

	std::vector<Component *>::iterator it;
	for (it = this->components[tadPole::ComponentType::MESH].begin(); it != this->components[tadPole::ComponentType::MESH].end(); ++it)
	{
		((MeshComponent *)(*it))->setActive(active);
	}
}

void tadPole::GameObject::setParent(GameObject * parent)
{
	if (this->parentObject == NULL)
	{
		EXCEPTION("Cannot set the parent of the root object of a Scene.");
	}

	this->parentObject->sceneNode->removeChild(this->sceneNode);
	this->parentObject = parent;
	this->parentObject->sceneNode->addChild(this->sceneNode);

	this->parentObject->children.push_back(this);
}

void tadPole::GameObject::setParentInPlace(GameObject * parent)
{
	glm::vec3 worldPosition = getWorldPosition();
	glm::quat worldOrientation = getWorldOrientation();
	glm::vec3 worldScale = getWorldScale();

	parent->sceneNode->_update(false, true);
	Ogre::Vector3 newWorldPositionOgre = parent->sceneNode->convertWorldToLocalPosition(Ogre::Vector3(worldPosition.x, worldPosition.y, worldPosition.z));
	Ogre::Quaternion newWorldOrientationOgre = parent->sceneNode->convertWorldToLocalOrientation(Ogre::Quaternion(worldOrientation.w, worldOrientation.x, worldOrientation.y, worldOrientation.z));
	Ogre::Vector3 parentScaleOgre = parent->sceneNode->_getDerivedScale();
	glm::vec3 newWorldScale = glm::vec3(worldScale.x / parentScaleOgre.x, worldScale.y / parentScaleOgre.y, worldScale.z / parentScaleOgre.z);

	this->setPosition(newWorldPositionOgre.x, newWorldPositionOgre.y, newWorldPositionOgre.z);
	this->setOrientation(newWorldOrientationOgre.x, newWorldOrientationOgre.y, newWorldOrientationOgre.z, newWorldOrientationOgre.w);
	this->setScale(newWorldScale);

	this->setParent(parent);
}

void tadPole::GameObject::setPyObject(PyTadPole_GameObject * pyObject)
{
	this->pythonGameObject = pyObject;
}

void tadPole::GameObject::setPosition(glm::vec3 position)
{
	this->setPosition(position.x, position.y, position.z);
}

void tadPole::GameObject::setPosition(float x, float y, float z)
{
	this->sceneNode->setPosition(Ogre::Vector3(x, y, z));
}

void tadPole::GameObject::setOrientation(glm::vec3 axis, float angleDegrees)
{
	this->setOrientation(axis.x, axis.y, axis.z, angleDegrees);
}

void tadPole::GameObject::setOrientation(float axisX, float axisY, float axisZ, float angleDegrees)
{
	this->sceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(angleDegrees), Ogre::Vector3(axisX, axisY, axisZ)));
}

void tadPole::GameObject::setScale(float scale)
{
	this->setScale(scale, scale, scale);
}

void tadPole::GameObject::setScale(glm::vec3 scale)
{
	this->setScale(scale.x, scale.y, scale.z);
}

void tadPole::GameObject::setScale(float x, float y, float z)
{
	this->sceneNode->setScale(Ogre::Vector3(x, y, z));
}

void tadPole::GameObject::translateLocal(glm::vec3 translation)
{
	this->translateLocal(translation.x, translation.y, translation.z);
}

void tadPole::GameObject::translateLocal(float x, float y, float z)
{
	this->sceneNode->translate(x, y, z, Ogre::Node::TS_LOCAL);
}

void tadPole::GameObject::translateWorld(glm::vec3 translation)
{
	this->translateWorld(translation.x, translation.y, translation.z);
}

void tadPole::GameObject::translateWorld(float x, float y, float z)
{
	this->sceneNode->translate(x, y, z, Ogre::Node::TS_WORLD);
}

void tadPole::GameObject::rotateLocal(glm::vec3 axis, float angleDegrees)
{
	this->rotateLocal(axis.x, axis.y, axis.z, angleDegrees);
}

void tadPole::GameObject::rotateLocal(float axisX, float axisY, float axisZ, float angleDegrees)
{
	this->sceneNode->rotate(
		Ogre::Vector3(axisX, axisY, axisZ),
		Ogre::Degree(angleDegrees), Ogre::Node::TS_LOCAL);
}

void tadPole::GameObject::rotateWorld(glm::vec3 axis, float angleDegrees)
{
	this->rotateWorld(axis.x, axis.y, axis.z, angleDegrees);
}

void tadPole::GameObject::rotateWorld(float axisX, float axisY, float axisZ, float angleDegrees)
{
	this->sceneNode->rotate(
		Ogre::Vector3(axisX, axisY, axisZ),
		Ogre::Degree(angleDegrees), Ogre::Node::TS_WORLD);
}

void tadPole::GameObject::scale(float scale)
{
	this->scale(scale, scale, scale);
}

void tadPole::GameObject::scale(glm::vec3 scale)
{
	this->scale(scale.x, scale.y, scale.z);
}

void tadPole::GameObject::scale(float x, float y, float z)
{
	this->sceneNode->scale(x, y, z);
}

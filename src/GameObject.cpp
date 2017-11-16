#include "stdafx.h"
#include "GameObject.h"

#include "Application.h"
#include "Component.h"
#include "MeshComponent.h"

tadPole::GameObject::GameObject(std::string name)
{
	this->name = name;
	this->active = true;
	this->components = std::map<tadPole::ComponentType, std::vector<Component *>>();

	this->initialize();
}

tadPole::GameObject::~GameObject()
{
	this->parentSceneNode->removeChild(this->sceneNode);
	this->sceneNode->detachAllObjects();
	RENDER_MANAGER->sceneManager->destroySceneNode(this->sceneNode);

	std::map<tadPole::ComponentType, std::vector<Component *>>::iterator map_it;
	for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
	{
		std::vector<Component *>::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			delete *vector_it;
		}
	}
}

void tadPole::GameObject::initialize()
{
	this->parentSceneNode = RENDER_MANAGER->sceneManager->getRootSceneNode();
	this->sceneNode = this->parentSceneNode->createChildSceneNode();
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
	this->parentSceneNode->removeChild(this->sceneNode);
	this->parentSceneNode = parent->sceneNode;
	this->parentSceneNode->addChild(this->sceneNode);
}
void tadPole::GameObject::setScaleInheritance(bool inherit)
{
	this->sceneNode->setInheritScale(inherit);
}
void tadPole::GameObject::setOrientationInheritance(bool inherit)
{
	this->sceneNode->setInheritOrientation(inherit);
}

void tadPole::GameObject::setPosition(glm::vec3 position)
{
	this->setPosition(position.x, position.y, position.z);
}
void tadPole::GameObject::setPosition(float x, float y, float z)
{
	this->sceneNode->setPosition(Ogre::Vector3(x, y, z));
}
void tadPole::GameObject::setOrientation(glm::quat orientation)
{
	this->setOrientation(orientation.x, orientation.y, orientation.z, orientation.w);
}
void tadPole::GameObject::setOrientation(glm::vec3 axis, float angle_degrees)
{
	this->setOrientation(axis.x, axis.y, axis.z, angle_degrees);
}
void tadPole::GameObject::setOrientation(float x, float y, float z, float w)
{
	this->sceneNode->setOrientation(w, x, y, z);
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
void tadPole::GameObject::rotateLocal(glm::quat rotation)
{
	this->rotateLocal(rotation.x, rotation.y, rotation.z, rotation.w);
}
void tadPole::GameObject::rotateLocal(glm::vec3 axis, float angle_degrees)
{
	this->rotateLocal(axis.x, axis.y, axis.z, angle_degrees);
}
void tadPole::GameObject::rotateLocal(float axis_x, float axis_y, float axis_z, float angle_degrees)
{
	this->sceneNode->rotate(
		Ogre::Vector3(axis_x, axis_y, axis_z), 
		Ogre::Degree(angle_degrees), Ogre::Node::TS_LOCAL);
}
void tadPole::GameObject::rotateWorld(glm::quat rotation)
{
	this->rotateWorld(rotation.x, rotation.y, rotation.z, rotation.w);
}
void tadPole::GameObject::rotateWorld(glm::vec3 axis, float angle_degrees)
{
	this->rotateWorld(axis.x, axis.y, axis.z, angle_degrees);
}
void tadPole::GameObject::rotateWorld(float axis_x, float axis_y, float axis_z, float angle_degrees)
{
	this->sceneNode->rotate(
		Ogre::Vector3(axis_x, axis_y, axis_z), 
		Ogre::Degree(angle_degrees), Ogre::Node::TS_WORLD);
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

tadPole::MeshComponent * tadPole::GameObject::createMeshComponent(std::string fname)
{
	MeshComponent * meshComponent = new MeshComponent(this, fname);
	this->components[ComponentType::MESH].push_back(meshComponent);
	this->sceneNode->attachObject(meshComponent->entity);
	meshComponent->setActive(this->active);

	return meshComponent;
}

void tadPole::GameObject::update(float deltaTime)
{
	std::map<tadPole::ComponentType, std::vector<Component *>>::iterator map_it;
	for (map_it = this->components.begin(); map_it != this->components.end(); ++map_it)
	{
		std::vector<Component * >::iterator vector_it;
		for (vector_it = map_it->second.begin(); vector_it != map_it->second.end(); ++vector_it)
		{
			((Component*)(*vector_it))->update(deltaTime);
		}
	}
}

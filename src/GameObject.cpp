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
		std::vector<Component * >::iterator vector_it;
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

void tadPole::GameObject::setPosition(float x, float y, float z)
{
	Ogre::Vector3 position = Ogre::Vector3(x, y, z);
	this->sceneNode->setPosition(position);
}

void tadPole::GameObject::setScale(float x, float y, float z)
{
	Ogre::Vector3 scale = Ogre::Vector3(x, y, z);
	this->sceneNode->setScale(scale);
}

void tadPole::GameObject::setOrientation(float axis_x, float axis_y, float axis_z, float angle_degrees)
{
	Ogre::Vector3 axis = Ogre::Vector3(axis_x, axis_y, axis_z);
	Ogre::Radian angle = Ogre::Radian(angle_degrees);
	Ogre::Quaternion orientation = Ogre::Quaternion(angle, axis);
	this->sceneNode->setOrientation(orientation);
}

void tadPole::GameObject::setOrientation(Ogre::Quaternion orientation)
{
	this->sceneNode->setOrientation(orientation);
}

void tadPole::GameObject::rotateWorld(float axis_x, float axis_y, float axis_z, float angle_degrees)
{
	this->sceneNode->rotate(Ogre::Vector3(axis_x, axis_y, axis_z), Ogre::Degree(angle_degrees), Ogre::Node::TS_WORLD);
}

void tadPole::GameObject::rotateParent(float axis_x, float axis_y, float axis_z, float angle_degrees)
{
	this->sceneNode->rotate(Ogre::Vector3(axis_x, axis_y, axis_z), Ogre::Degree(angle_degrees), Ogre::Node::TS_PARENT);
}

void tadPole::GameObject::rotateLocal(float axis_x, float axis_y, float axis_z, float angle_degrees)
{
	this->sceneNode->rotate(Ogre::Vector3(axis_x, axis_y, axis_z), Ogre::Degree(angle_degrees), Ogre::Node::TS_LOCAL);
}

void tadPole::GameObject::translateWorld(float x, float y, float z)
{
	this->sceneNode->translate(x, y, z, Ogre::Node::TS_WORLD);
}

void tadPole::GameObject::translateParent(float x, float y, float z)
{
	this->sceneNode->translate(x, y, z, Ogre::Node::TS_PARENT);
}

void tadPole::GameObject::translateLocal(float x, float y, float z)
{
	this->sceneNode->translate(x, y, z, Ogre::Node::TS_LOCAL);
}

void tadPole::GameObject::scale(float x, float y, float z)
{
	this->sceneNode->scale(x, y, z);
}

Ogre::Quaternion tadPole::GameObject::getRelativeOrientation()
{
	return this->sceneNode->getOrientation();
}

Ogre::Quaternion tadPole::GameObject::getWorldOrientation()
{
	return this->sceneNode->_getDerivedOrientation();
}

tadPole::Vector3 tadPole::GameObject::getRelativePosition()
{
	Ogre::Vector3 position = this->sceneNode->getPosition();
	return Vector3(position.x, position.y, position.z);
}

tadPole::Vector3 tadPole::GameObject::getWorldPosition()
{
	Ogre::Vector3 position = this->sceneNode->_getDerivedPosition();
	return Vector3(position.x, position.y, position.z);
}

tadPole::Vector3 tadPole::GameObject::getRelativeScale()
{
	Ogre::Vector3 scale = this->sceneNode->getScale();
	return Vector3(scale.x, scale.y, scale.z);
}

tadPole::Vector3 tadPole::GameObject::getWorldScale()
{
	Ogre::Vector3 scale = this->sceneNode->_getDerivedScale();
	return Vector3(scale.x, scale.y, scale.z);
}

tadPole::MeshComponent * tadPole::GameObject::createMeshComponent(std::string fname)
{
	MeshComponent * meshComponent = new MeshComponent("", this, fname);
	this->components[ComponentType::MESH].push_back(meshComponent);
	meshComponent->attach(this->sceneNode);
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

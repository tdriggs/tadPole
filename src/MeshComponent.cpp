#include "stdafx.h"
#include "MeshComponent.h"

#include "RenderManager.h"
#include "GameObject.h"

using namespace tadPole;

tadPole::MeshComponent::MeshComponent(std::string n, GameObject * g, std::string fname) : Component(n, g)
{
	this->fname = fname;

	this->initialize();
}

tadPole::MeshComponent::~MeshComponent()
{
	RENDER_MANAGER->sceneManager->destroyEntity(this->entity);
}

void tadPole::MeshComponent::initialize()
{
	this->entity = RENDER_MANAGER->sceneManager->createEntity(this->fname);
}

void tadPole::MeshComponent::attach(Ogre::SceneNode * sceneNode)
{
	sceneNode->attachObject(this->entity);
}

void tadPole::MeshComponent::setActive(bool active)
{
	Component::setActive(active);

	this->entity->setVisible(active);
}

ComponentType tadPole::MeshComponent::getType()
{
	return ComponentType::MESH;
}

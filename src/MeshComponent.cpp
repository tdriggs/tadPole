#include "stdafx.h"
#include "MeshComponent.h"

#include "RenderManager.h"
#include "GameObject.h"

tadPole::MeshComponent::MeshComponent(GameObject * g, std::string fileName) : Component(g)
{
	this->fileName = fileName;

	this->initialize();
}

tadPole::MeshComponent::~MeshComponent()
{
	RENDER_MANAGER->sceneManager->destroyEntity(this->entity);
}

void tadPole::MeshComponent::initialize()
{
	this->entity = RENDER_MANAGER->sceneManager->createEntity(this->fileName);
}

void tadPole::MeshComponent::setActive(bool active)
{
	Component::setActive(active);

	this->entity->setVisible(active);
}

tadPole::ComponentType tadPole::MeshComponent::getType()
{
	return ComponentType::MESH;
}

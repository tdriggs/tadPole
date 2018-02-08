#include "stdafx.h"
#include "MeshComponent.h"

#include "RenderManager.h"
#include "GameObject.h"

tadPole::MeshComponent::MeshComponent(GameObject * g, std::string fileName) : Component(g)
{
	this->fileName = fileName;

	this->entity = RENDER_MANAGER->sceneManager->createEntity(g->getName() + "_mesh_" + std::to_string(g->getComponentCount(ComponentType::MESH)), fileName);
}

tadPole::MeshComponent::~MeshComponent()
{
	if (this->entity != NULL)
	{
		if (this->entity->getParentSceneNode())
		{
			this->entity->getParentSceneNode()->detachObject(this->entity);
		}
		RENDER_MANAGER->sceneManager->destroyEntity(this->entity);
	}
}

void tadPole::MeshComponent::setActive(bool active)
{
	this->entity->setVisible(active);
}

tadPole::ComponentType tadPole::MeshComponent::getType()
{
	return ComponentType::MESH;
}

std::string tadPole::MeshComponent::serialize()
{
	std::ostringstream result;

	result << "{\n\t\t\t\t\t\t\t\"type\": \"" << "MESH" << "\",\n\t\t\t\t\t\t\t\"fileName\": \"" << this->fileName << "\"\n\t\t\t\t\t\t}";

	return result.str();
}

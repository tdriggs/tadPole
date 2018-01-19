#include "stdafx.h"
#include "CameraComponent.h"

#include "RenderManager.h"
#include "GameObject.h"
#include "Exception.h"

tadPole::CameraComponent::CameraComponent(GameObject * g) : Component(g)
{
	this->camera = RENDER_MANAGER->sceneManager->createCamera(g->getName() + "_camera_" + std::to_string(g->getComponentCount(ComponentType::CAMERA)));
	this->camera->setAutoAspectRatio(true);
}

tadPole::CameraComponent::~CameraComponent()
{
	if (this->camera != NULL)
	{
		if (this->camera->getParentSceneNode())
		{
			this->camera->getParentSceneNode()->detachObject(this->camera);
		}
		RENDER_MANAGER->sceneManager->destroyCamera(this->camera);
	}
}

void tadPole::CameraComponent::setActive(bool active)
{
	this->camera->setVisible(active);
}

tadPole::ComponentType tadPole::CameraComponent::getType()
{
	return tadPole::ComponentType::CAMERA;
}

std::string tadPole::CameraComponent::serialize()
{
	std::ostringstream result;
	std::ostringstream directionString;
	Ogre::Vector3 direction = this->camera->getDerivedDirection();
	directionString << "[" << direction.x << ", " << direction.y << ", " << direction.z << "]";

	result << "{\n\t\t\t\t\t\t\t\"type\": \"" << "CAMERA" << "\",\n\t\t\t\t\t\t\t\"direction\": " << directionString.str()
		<< ",\n\t\t\t\t\t\t\t\"nearClipDistance\": " << this->camera->getNearClipDistance() << ",\n\t\t\t\t\t\t\t\"farClipDistance\": " << this->camera->getFarClipDistance()
		<< ",\n\t\t\t\t\t\t\t\"viewport\": \"" << ((this->camera->getViewport() == RENDER_MANAGER->mainViewport) ? "MAIN" : "") << "\"\n\t\t\t\t\t\t}";

	return result.str();
}

void tadPole::CameraComponent::setDirection(glm::vec3 direction)
{
	this->camera->setDirection(Ogre::Vector3(direction.x, direction.y, direction.z));
}

void tadPole::CameraComponent::setClipDistances(float n, float f)
{
	this->camera->setNearClipDistance(n);
	this->camera->setFarClipDistance(f);
}

void tadPole::CameraComponent::setViewport(std::string viewport)
{
	if (viewport == "MAIN")
	{
		RENDER_MANAGER->mainViewport->setCamera(this->camera);
	}
	else if (viewport != "")
	{
		EXCEPTION("Viewport does not exist: " + viewport);
	}
}

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

	int viewportIndex = -1;
	for (int i = 0; i < RENDER_MANAGER->renderWindow->getNumViewports(); ++i)
	{
		if (this->camera->getViewport() == RENDER_MANAGER->renderWindow->getViewport(i))
		{
			viewportIndex = i;
			break;
		}
	}

	result << "{\n\t\t\t\t\t\t\t\"type\": \"" << "CAMERA" << "\",\n\t\t\t\t\t\t\t\"nearClipDistance\": " << this->camera->getNearClipDistance() << ",\n\t\t\t\t\t\t\t\"farClipDistance\": " << this->camera->getFarClipDistance()
		<< ",\n\t\t\t\t\t\t\t\"viewport\": " << std::to_string(viewportIndex) << "\n\t\t\t\t\t\t}";

	return result.str();
}

void tadPole::CameraComponent::setPyObject(PyTadPole_CameraComponent * pyObject)
{
	this->pyObject = pyObject;
}

tadPole::PyTadPole_CameraComponent * tadPole::CameraComponent::getPyObject()
{
	return this->pyObject;
}

void tadPole::CameraComponent::setClipDistances(float n, float f)
{
	this->camera->setNearClipDistance(n);
	this->camera->setFarClipDistance(f);
}

void tadPole::CameraComponent::setViewport(int viewport)
{
	if (viewport >= RENDER_MANAGER->renderWindow->getNumViewports() || viewport < 0)
	{
		EXCEPTION("Viewport does not exist: " + std::to_string(viewport));
	}

	RENDER_MANAGER->renderWindow->getViewport(viewport)->setCamera(this->camera);
}

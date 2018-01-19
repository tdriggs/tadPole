#include "stdafx.h"
#include "LightComponent.h"

#include "RenderManager.h"
#include "GameObject.h"

tadPole::LightComponent::LightComponent(GameObject * g, LightType type) : Component(g)
{
	this->light = RENDER_MANAGER->sceneManager->createLight(g->getName() + "_light_" + std::to_string(g->getComponentCount(ComponentType::LIGHT)));

	this->type = type;
	if (this->type == LightType::DIRECTIONAL)
		this->light->setType(Ogre::Light::LT_DIRECTIONAL);
	else if (this->type == LightType::POINT)
		this->light->setType(Ogre::Light::LT_POINT);
	else if (this->type == LightType::SPOT)
		this->light->setType(Ogre::Light::LT_SPOTLIGHT);
}

tadPole::LightComponent::~LightComponent()
{
	if (this->light != NULL)
	{
		if (this->light->getParentSceneNode())
		{
			this->light->getParentSceneNode()->detachObject(this->light);
		}
		RENDER_MANAGER->sceneManager->destroyLight(this->light);
	}
}

void tadPole::LightComponent::setActive(bool active)
{
	this->light->setVisible(active);
}

tadPole::ComponentType tadPole::LightComponent::getType()
{
	return tadPole::ComponentType::LIGHT;
}

std::string tadPole::LightComponent::serialize()
{
	std::ostringstream result;
	std::ostringstream directionString;
	std::ostringstream diffuseString;
	std::ostringstream specularString;
	Ogre::Vector3 direction = this->light->getDerivedDirection();
	Ogre::ColourValue diffuseColor = this->light->getDiffuseColour();
	Ogre::ColourValue specularColor = this->light->getSpecularColour();
	directionString << "[" << direction.x << ", " << direction.y << ", " << direction.z << "]";
	diffuseString << "[" << diffuseColor.r << ", " << diffuseColor.g << ", " << diffuseColor.b << "]";
	specularString << "[" << specularColor.r << ", " << specularColor.g << ", " << specularColor.b << "]";

	std::string lightTypeString = (this->type == LightType::DIRECTIONAL) ? "DIRECTIONAL" : ((this->type == LightType::POINT) ? "POINT" : "SPOT");

	result << "{\n\t\t\t\t\t\t\t\"type\": \"" << "LIGHT" << "\",\n\t\t\t\t\t\t\t\"lightType\": \"" << lightTypeString << "\",\n\t\t\t\t\t\t\t\"direction\": " << directionString.str()
		<< ",\n\t\t\t\t\t\t\t\"diffuseColor\": " << diffuseString.str() << ",\n\t\t\t\t\t\t\t\"specularColor\": " << specularString.str() << ",\n\t\t\t\t\t\t\t\"spotlightInnerAngle\": " 
		<< this->light->getSpotlightInnerAngle().valueRadians() << ",\n\t\t\t\t\t\t\t\"spotlightOuterAngle\": " << this->light->getSpotlightOuterAngle().valueRadians() << "\n\t\t\t\t\t\t}";

	return result.str();
}

void tadPole::LightComponent::setDirection(glm::vec3 direction)
{
	this->light->setDirection(Ogre::Vector3(direction.x, direction.y, direction.z));
}

void tadPole::LightComponent::setDiffuseColor(float r, float g, float b)
{
	this->light->setDiffuseColour(Ogre::ColourValue(r, g, b));
}

void tadPole::LightComponent::setSpecularColor(float r, float g, float b)
{
	this->light->setSpecularColour(Ogre::ColourValue(r, g, b));
}

void tadPole::LightComponent::setSpotlightAngles(float innerAngle, float outerAngle)
{
	this->light->setSpotlightRange(Ogre::Degree(innerAngle), Ogre::Degree(outerAngle));
}

#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	/**
	* The type of light to render.
	*/
	enum class LightType { POINT, DIRECTIONAL, SPOT };

	/**
	* A component that represents a type of light (given by LightType) to render from the location of
	* the owner GameObject.
	*/
	class LightComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		Ogre::Light * light;	///< The OGRE representation of the LightComponent.
		LightType type;			///< The type of light to render for this LightComponent.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* LightComponent constructor.
		*/
		LightComponent(
			GameObject * g,		///< The GameObject to which this LightComponent is connected.
			LightType type		///< The type of light that this LightComponent is going to render.
		);

		/**
		* LightComponent destructor.
		*/
		~LightComponent();


		// @@@@@ BASE CLASS / INTERFACE METHODS @@@@@
	public:
		/**
		* Set whether this Component is visible and can be interacted with in its Scene.
		*/
		void setActive(
			bool active	///< Whether this Component is visible in the scene and can be interacted with.
		);

		/**
		* Get the ComponentType of this Component.
		*/
		ComponentType getType();

		/**
		* Turn this GameObject into a std::string of valid, formatted JSON.
		*/
		std::string serialize();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Set the direction that this LightComponent is pointing.
		*/
		void setDirection(
			glm::vec3 direction	///< The new direction of this LightComponent.
		);

		/**
		* Set the diffuse color of the light that this LightComponent will render.
		*/
		void setDiffuseColor(
			float r,	///< The red value of the diffuse light that this LightComponent will render.
			float g,	///< The green value of the diffuse light that this LightComponent will render.
			float b		///< The blue value of the diffuse light that this LightComponent will render.
		);

		/**
		* Set the specular color of the light that this LightComponent will render.
		*/
		void setSpecularColor(
			float r,	///< The red value of the specular light that this LightComponent will render.
			float g,	///< The green value of the specular light that this LightComponent will render.
			float b		///< The blue value of the specular light that this LightComponent will render.
		);

		/**
		* Set the inner and outer angles of the spotlight cone. If this LightComponent is
		* not a spotlight, this method has no affect.
		*/
		void setSpotlightAngles(
			float innerAngle,	///< The inner angle of the spotlight cone of this LightComponent.
			float outerAngle	///< The outer angle of the spotlight cone of this LightComponent.
		);
	};
}

#endif

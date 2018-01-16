#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	/**
	* 
	*/
	enum class LightType { POINT, DIRECTIONAL, SPOT };

	/**
	*
	*/
	class LightComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		Ogre::Light * light;	///<
		LightType type;			///<


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		*
		*/
		LightComponent(
			GameObject * g,		///<
			LightType type		///<
		);

		/**
		*
		*/
		~LightComponent();


		// @@@@@ BASE CLASS / INTERFACE METHODS @@@@@
	public:
		/**
		*
		*/
		void setActive(
			bool active	///<
		);

		/**
		*
		*/
		ComponentType getType();

		/**
		*
		*/
		std::string serialize();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		*
		*/
		void setDirection(
			glm::vec3 direction	///<
		);

		/**
		*
		*/
		void setDiffuseColor(
			float r,	///<
			float g,	///<
			float b		///<
		);

		/**
		*
		*/
		void setSpecularColor(
			float r,	///<
			float g,	///<
			float b		///<
		);

		/**
		*
		*/
		void setSpotlightAngles(
			float innerAngle,	///<
			float outerAngle	///<
		);
	};
}

#endif

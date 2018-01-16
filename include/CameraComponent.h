#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	/**
	* 
	*/
	class CameraComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		Ogre::Camera * camera;	///<


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		*
		*/
		CameraComponent(
			GameObject * g	///<
		);

		/**
		*
		*/
		~CameraComponent();


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


		// @@@@@ GENERAL SETTERS @@@@@
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
		void setClipDistances(
			float n,	///<
			float f		///<
		);

		/**
		*
		*/
		void setViewport(
			std::string viewport	///<
		);
	};
}

#endif

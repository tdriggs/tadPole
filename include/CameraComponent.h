#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	/**
	* A component that can be attached to a viewport and display what is within the area of display, decided by the clip distances.
	*/
	class CameraComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		Ogre::Camera * camera;	///< The OGRE representation of the component.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* CameraComponent constructor.
		*/
		CameraComponent(
			GameObject * g	///< The GameObject to which this CameraComponent is connected.
		);

		/**
		* CameraComponent destructor.
		*/
		~CameraComponent();


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


		// @@@@@ GENERAL SETTERS @@@@@
	public:
		/**
		* Set the direction that the CameraComponent is pointing.
		*/
		void setDirection(
			glm::vec3 direction	///< The new direction for the CameraComponent to point.
		);

		/**
		* Set the near and far clip distances of the CameraComponent.
		*/
		void setClipDistances(
			float n,	///< The near clip distance of the CameraComponent.
			float f		///< The far clip distance of the CameraComponent.
		);

		/**
		* Attach this CameraComponent to a viewport by name. The given viewport will display what
		* this CameraComponent is pointing towards.
		*/
		void setViewport(
			std::string viewport	///< The name of the new viewport to attach to this CameraComponent.
		);
	};
}

#endif

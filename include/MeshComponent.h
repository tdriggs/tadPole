#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"
#include "PyTadPoleMeshComponent.h"

namespace tadPole
{
	class GameObject;

	/**
	* A component that represents a mesh that is rendered at the location of the parent GameObject.
	*/
	class MeshComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		std::string fileName;	///< The name of the file in which the mesh is located.
		Ogre::Entity * entity;	///< The OGRE representation of this MeshComponent.
		PyTadPole_MeshComponent * pyObject;


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* MeshComponent constructor.
		*/
		MeshComponent(
			GameObject * g,			///< The GameObject to which this MeshComponent is connected.
			std::string fileName	///< The name of the file in which the mesh is located.
		);

		/**
		* MeshComponent destructor.
		*/
		~MeshComponent();


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
		* Sets the PyObject of this MeshComponent.
		*/
		void setPyObject(
			PyTadPole_MeshComponent * pyObject	///< the new PyObject for this MeshComponent.
		);

		/**
		* Gets the PyObject of this MeshComponent.
		*/
		PyTadPole_MeshComponent * getPyObject();
	};
}


#endif

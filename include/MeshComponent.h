#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	/**
	* 
	*/
	class MeshComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		std::string fileName;	///<
		Ogre::Entity * entity;	///<


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		*
		*/
		MeshComponent(
			GameObject * g,			///<
			std::string fileName	///<
		);

		/**
		*
		*/
		~MeshComponent();


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
	};
}


#endif

#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	class MeshComponent : public Component
	{
		friend class GameObject;

	protected:
		std::string fileName;
		Ogre::Entity * entity;

	public:
		MeshComponent(GameObject * g, std::string fileName);
		~MeshComponent();

		void initialize();
		void setActive(bool active);

		ComponentType getType();
	};
}


#endif

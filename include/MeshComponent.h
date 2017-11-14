#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "stdafx.h"

#include <string>

#include "ComponentType.h"
#include "Component.h"

namespace tadPole
{
	class GameObject;

	class MeshComponent : public Component
	{
	protected:
		std::string fname;
		Ogre::Entity * entity;

	public:
		MeshComponent(std::string n, GameObject * g, std::string fname);
		~MeshComponent();

		void initialize();
		void attach(Ogre::SceneNode * sceneNode);
		void setActive(bool active);

		ComponentType getType();
	};
}


#endif

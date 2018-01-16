#ifndef TADPOLE_COMPONENT_H
#define TADPOLE_COMPONENT_H

#include "stdafx.h"

#include <string>

#include "Serializable.h"
#include "ComponentType.h"

namespace tadPole
{	
	class GameObject;

	class Component: Serializable
	{
	protected:
		GameObject * owner;

	public:
		Component(GameObject * g) : owner(g) {}
		virtual ~Component() { }

		virtual void update(float deltaTime) {}

		virtual std::string serialize() = 0;
		virtual ComponentType getType() = 0;

		virtual void setActive(bool active) = 0;

		GameObject * getOwner() 
		{
			return this->owner;
		}
	};
}

#endif

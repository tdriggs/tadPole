#ifndef TADPOLE_COMPONENT_H
#define TADPOLE_COMPONENT_H

#include "stdafx.h"

#include <string>

#include "ComponentType.h"

namespace tadPole
{	
	class GameObject;

	class Component
	{
	protected:
		GameObject * owner;
		bool isActive = true;

	public:
		Component(GameObject * g) : owner(g) {}
		virtual ~Component() { }

		virtual void update(float deltaTime) {}

		virtual ComponentType getType() = 0;

		GameObject * getOwner() 
		{
			return this->owner;
		}

		void setActive(bool active) 
		{
			this->isActive = active;
		}
	};
}

#endif

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
		std::string name;
		GameObject * owner;
		bool isActive = true;

	public:
		Component(std::string n, GameObject * g) : owner(g), name(n) {}
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

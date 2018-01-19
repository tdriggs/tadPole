#ifndef COMPONENT_H
#define COMPONENT_H

#include "stdafx.h"

#include <string>
#include "Serializable.h"
#include "ComponentType.h"

namespace tadPole
{	
	class GameObject;

	/**
	* An object that will be connected to a GameObject and have some affect on the that GameObject,
	* GameObejcts around it, or the Scene itself.
	*/
	class Component: public Serializable
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		GameObject * owner;		///< The GameObject to which this Component is connected.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Component constructor.
		*/
		Component(
			GameObject * g		///< The GameObject to which this Component is connected.
		) : owner(g) {}

		/**
		* Comopnent destructor.
		*/
		virtual ~Component() {}


		// @@@@@ BASE CLASS / INTERFACE METHODS @@@@@
	public:
		/**
		* Turn this Component into a std::string of valid, formatted JSON.
		*/
		virtual std::string serialize() = 0;


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		*
		*/
		virtual void update(
			float deltaTime		///< The time that has passed since the last frame in seconds.
		) {}


		// @@@@@ GENERAL GETTERS @@@@@
	public:
		/**
		* Get the ComponentType of this Component.
		*/
		virtual ComponentType getType() = 0;

		/**
		* Get the GameObject to which this Component is connected.
		*/
		GameObject * getOwner()
		{
			return this->owner;
		}


		// @@@@@ GENERAL SETTERS @@@@@
	public:
		/**
		* Set whether this Component is visible and can be interacted with in its Scene.
		*/
		virtual void setActive(
			bool active		///< Whether this Component is visible in the scene and can be interacted with.
		) = 0;
	};
}

#endif

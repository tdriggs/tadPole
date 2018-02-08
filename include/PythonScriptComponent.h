#ifndef PYTHON_SCRIPT_COMPONENT_H
#define PYTHON_SCRIPT_COMPONENT_H

#include "stdafx.h"

#include "ComponentType.h"
#include "Component.h"
#include "PyTadPoleScriptComponent.h"

namespace tadPole
{
	class GameObject;

	/**
	*
	*/
	class PythonScriptComponent : public Component
	{
		// @@@@@ FRIENDS @@@@@
		friend class GameObject;


		// @@@@@ ATTRIBUTES @@@@@
	protected:
		bool active;
		std::string scriptName;
		std::string className;
		PyObject * tadPoleModule;
		PyObject * pyObject;


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* PythonScriptComponent constructor.
		*/
		PythonScriptComponent(
			GameObject * g,
			std::string scriptName
		);

		/**
		* PythonScriptComponent destructor.
		*/
		~PythonScriptComponent();


		// @@@@@ BASE CLASS / INTERFACE METHODS @@@@@
	public:
		/**
		*
		*/
		void update(
			float deltaTime		///< The time that has passed since the last frame in seconds.
		);

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


		// @@@@@ GENERAL GETTERS @@@@@
	public:
		/**
		* Return the script name of this PythonScriptComponent.
		*/
		std::string getScriptName();

		/**
		* Return the class name of the class of this PythonScriptComponent.
		*/
		std::string getClassName();

		/**
		* Return the module that contains this PythonScriptComponent.
		*/
		PyObject * getModule();


		// @@@@@ GENERAL SETTERS @@@@@
	public:
		/**
		* Sets the PyObject of this PythonScriptComponent.
		*/
		void setPyObject(
			PyObject * pyObject	///< the new PyObject for this PythonScriptComponent.
		);

		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Executes a callback method on the attached PyObject if it exists.
		*/
		void executeCallback(
			std::string callbackName	///< The name of the callback method to execute.
		);
	};
}

#endif

#ifndef PYTHON_SCRIPT_MANAGER_H
#define PYTHON_SCRIPT_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"
#include "GameObject.h"
#include "PythonScriptComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"

#define SCRIPT_LOCATION "Python Scripts/"
#define PYTHON_SCRIPT_MANAGER tadPole::PythonScriptManager::getInstance()	///< Convnenience macro for access to the singleton instance.

namespace tadPole
{
	/**
	* Serves as the access point to the Python interperter that it manages.
	*/
	class PythonScriptManager : public Singleton<PythonScriptManager>
	{
		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* PythonScriptManager constructor.
		*/
		PythonScriptManager();

		/**
		* PythonScriptManager destructor.
		*/
		~PythonScriptManager();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Executes a Python script. The full stack trace for any errors is logged
		* by the LogManager.
		*/
		void executeScript(std::string scriptName);

		/**
		*
		*/
		void createPythonGameObject(
			GameObject * gameObject
		);

		/**
		*
		*/
		void createPythonScriptComponent(
			PythonScriptComponent * scriptComponent
		);

		/**
		*
		*/
		void createPythonMeshComponent(
			MeshComponent * meshComponent
		);

		/**
		*
		*/
		void createPythonCameraComponent(
			CameraComponent * cameraComponent
		);

		/**
		*
		*/
		void createPythonLightComponent(
			LightComponent * lightComponent
		);
	};
}

#endif

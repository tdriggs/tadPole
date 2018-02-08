#ifndef PY_TADPOLE_FUNCTIONS_H
#define PY_TADPOLE_FUNCTIONS_H

#include "stdafx.h"

namespace tadPole
{
	/**
	* Loads a Python script through the ScriptManager.
	*/
	PyObject * pyTadPole_loadScript(PyObject * self, PyObject * args);

	/**
	* Log a message through the LogManager.
	*/
	PyObject * pyTadPole_log(PyObject * self, PyObject * args);

	/**
	* Saves a scene through the Scene.
	*/
	PyObject * pyTadPole_saveScene(PyObject * self, PyObject * args);

	/**
	* Loads the scene through the Scene.
	*/
	PyObject * pyTadPole_loadScene(PyObject * self, PyObject * args);

	/**
	* Clears the scene through the Scene.
	*/
	PyObject * pyTadPole_clearScene(PyObject * self, PyObject * args);

	/**
	* Create a group through the Scene.
	*/
	PyObject * pyTadPole_createGroup(PyObject * self, PyObject * args);

	/**
	* Delete a group through the Scene.
	*/
	PyObject * pyTadPole_deleteGroup(PyObject * self, PyObject * args);

	/**
	* Set a group active through the Scene.
	*/
	PyObject * pyTadPole_setGroupActive(PyObject * self, PyObject * args);

	/**
	* Delete a GameObject through the Scene.
	*/
	PyObject * pyTadPole_deleteGameObject(PyObject * self, PyObject * args);

	/**
	* Get a group of GameObjects through the Scene.
	*/
	PyObject * pyTadPole_getGroup(PyObject * self, PyObject * args);

	/**
	* Get a GameObject through the Scene.
	*/
	PyObject * pyTadPole_getGameObject(PyObject * self, PyObject * args);
}

#endif

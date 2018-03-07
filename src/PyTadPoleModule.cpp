#include "stdafx.h"
#include "PyTadPoleModule.h"

#include "PyTadPoleFunctions.h"

extern PyTypeObject pyTadPole_GameObject_type;
extern PyTypeObject pyTadPole_ScriptComponent_type;
extern PyTypeObject pyTadPole_MeshComponent_type;
extern PyTypeObject pyTadPole_LightComponent_type;
extern PyTypeObject pyTadPole_CameraComponent_type;

PyMethodDef pyTadPoleModuleFunctions[] =
{
	{ "loadScript", tadPole::pyTadPole_loadScript, METH_VARARGS, "Loads a Python script through the ScriptManager." },
	{ "log", tadPole::pyTadPole_log, METH_VARARGS, "Logs a message through LogManager." },
	{ "saveScene", tadPole::pyTadPole_saveScene, METH_VARARGS, "Saves the scene through the Scene." },
	{ "loadScene", tadPole::pyTadPole_loadScene, METH_VARARGS, "Loads a scene through the Scene." },
	{ "clearScene", tadPole::pyTadPole_clearScene, METH_VARARGS, "Clears the scene through the Scene." },
	{ "createGroup", tadPole::pyTadPole_createGroup, METH_VARARGS, "Set a group active through the Scene." },
	{ "deleteGroup", tadPole::pyTadPole_deleteGroup, METH_VARARGS, "Delete a group through the Scene." },
	{ "setGroupActive", tadPole::pyTadPole_setGroupActive, METH_VARARGS, "Set a group active through the Scene." },
	{ "deleteGameObject", tadPole::pyTadPole_deleteGameObject, METH_VARARGS, "Delete a GameObject through the Scene." },
	{ "getGroup", tadPole::pyTadPole_getGroup, METH_VARARGS, "Get a group of GameObjects through the Scene." },
	{ "getGameObject", tadPole::pyTadPole_getGameObject, METH_VARARGS, "Get a GameObject through the Scene." },
	{ NULL, NULL, 0, NULL }
};

struct PyModuleDef pyTadPoleModule =
{
	PyModuleDef_HEAD_INIT,
	"pyTadPole",
	"A simple game engine for simple games.",
	-1,
	pyTadPoleModuleFunctions
};

PyMODINIT_FUNC tadPole::PyInit_tadPole()
{
	PyObject * module = PyModule_Create(&(pyTadPoleModule));
	if (module == NULL)
	{
		return NULL;
	}

	if (PyType_Ready(&pyTadPole_GameObject_type) < 0)
	{
		return NULL;
	}
	if (PyType_Ready(&pyTadPole_ScriptComponent_type) < 0)
	{
		return NULL;
	}
	if (PyType_Ready(&pyTadPole_MeshComponent_type) < 0)
	{
		return NULL;
	}
	if (PyType_Ready(&pyTadPole_LightComponent_type) < 0)
	{
		return NULL;
	}
	if (PyType_Ready(&pyTadPole_CameraComponent_type) < 0)
	{
		return NULL;
	}

	Py_INCREF(&pyTadPole_GameObject_type);
	PyModule_AddObject(module, "GameObject", (PyObject*)&pyTadPole_GameObject_type);
	Py_INCREF(&pyTadPole_ScriptComponent_type);
	PyModule_AddObject(module, "ScriptComponent", (PyObject*)&pyTadPole_ScriptComponent_type);
	Py_INCREF(&pyTadPole_MeshComponent_type);
	PyModule_AddObject(module, "MeshComponent", (PyObject*)&pyTadPole_MeshComponent_type);
	Py_INCREF(&pyTadPole_LightComponent_type);
	PyModule_AddObject(module, "LightComponent", (PyObject*)&pyTadPole_LightComponent_type);
	Py_INCREF(&pyTadPole_CameraComponent_type);
	PyModule_AddObject(module, "CameraComponent", (PyObject*)&pyTadPole_CameraComponent_type);

	return module;
}

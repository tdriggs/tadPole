#ifndef PY_TADPOLE_SCRIPT_COMPONENT
#define PY_TADPOLE_SCRIPT_COMPONENT

#include "stdafx.h"

namespace tadPole
{
	class PythonScriptComponent;

	typedef struct
	{
		PyObject_HEAD;
		PythonScriptComponent * scriptComponent;
	} PyTadPole_ScriptComponent;

	PyObject * pyTadPole_ScriptComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

	int pyTadPole_ScriptComponent_init(PyTadPole_ScriptComponent * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_ScriptComponent_str(PyTadPole_ScriptComponent * self);

	void pyTadPole_ScriptComponent_dealloc(PyTadPole_ScriptComponent * self);

	PyObject * pyTadPole_ScriptComponent_getGameObject(PyTadPole_ScriptComponent * self, PyObject * args, PyObject * kwargs);
}

#endif

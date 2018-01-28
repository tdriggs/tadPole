#ifndef PY_TADPOLE_GAME_OBJECT
#define PY_TADPOLE_GAME_OBJECT

#include "stdafx.h"
#include "GameObject.h"

namespace tadPole
{
	typedef struct
	{
		PyObject_HEAD;
		GameObject * gameObject;
	} PyTadPole_GameObject;

	PyObject * pyTadPole_GameObject_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

	int pyTadPole_GameObject_init(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_str(PyTadPole_GameObject * self);

	void pyTadPole_GameObject_dealloc(PyTadPole_GameObject * self);
}

#endif
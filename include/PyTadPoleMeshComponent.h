#ifndef PY_TADPOLE_MESH_COMPONENT
#define PY_TADPOLE_MESH_COMPONENT

#include "stdafx.h"

namespace tadPole
{
	class MeshComponent;

	typedef struct
	{
		PyObject_HEAD;
		MeshComponent * meshComponent;
	} PyTadPole_MeshComponent;

	PyObject * pyTadPole_MeshComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

	int pyTadPole_MeshComponent_init(PyTadPole_MeshComponent * self, PyObject * args, PyObject * kwargs);

	void pyTadPole_MeshComponent_dealloc(PyTadPole_MeshComponent * self);
}

#endif

#include "stdafx.h"
#include "PyTadPoleCameraComponent.h"

#include "Exception.h"
#include "CameraComponent.h"

PyObject * tadPole::pyTadPole_CameraComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{
	PyTadPole_CameraComponent * self = (PyTadPole_CameraComponent *)type->tp_alloc(type, 0);
	if (self)
	{
		self->cameraComponent = NULL;
	}

	return (PyObject *)self;
}

int tadPole::pyTadPole_CameraComponent_init(PyTadPole_CameraComponent * self, PyObject * args, PyObject * kwargs)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	return 0;
}

void tadPole::pyTadPole_CameraComponent_dealloc(PyTadPole_CameraComponent * self)
{
	if (!self->cameraComponent)
	{
		PyErr_SetString(PyExc_ValueError, "CameraComponent does not exist.");
	}

	delete self->cameraComponent->getOwner();
}

PyObject * tadPole::pyTadPole_CameraComponent_setClipDistances(PyTadPole_CameraComponent * self, PyObject * args, PyObject * kwargs)
{
	float n, f;
	if (!(
		(PyTuple_Size(args) == 2 && PyArg_ParseTuple(args, "ff", &n, &f))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->cameraComponent->setClipDistances(n, f);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_CameraComponent_setViewport(PyTadPole_CameraComponent * self, PyObject * args, PyObject * kwargs)
{
	int viewportIndex;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "i", &viewportIndex))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->cameraComponent->setViewport(viewportIndex);

	Py_RETURN_NONE;
}

PyMethodDef pyTadPole_CameraComponent_methods[] =
{
	{ "setClipDistances", (PyCFunction)tadPole::pyTadPole_CameraComponent_setClipDistances, METH_VARARGS, "" },
	{ "setViewport", (PyCFunction)tadPole::pyTadPole_CameraComponent_setViewport, METH_VARARGS, "" },
	{ NULL, NULL, 0, NULL }
};

PyTypeObject pyTadPole_CameraComponent_type =
{
	PyVarObject_HEAD_INIT(NULL, 0)							// Initializes the header
	"CameraComponent",										// tp_name
	sizeof(tadPole::PyTadPole_CameraComponent),				// tp_basicsize
	0,														// tp_itemsize
	(destructor)tadPole::pyTadPole_CameraComponent_dealloc,	// tp_dealloc
	0,														// tp_print
	0,														// tp_getattr
	0,														// tp_setattr
	0,														// tp_reserved
	0,														// tp_repr
	0,														// tp_as_number
	0,														// tp_as_sequence
	0,														// tp_as_mapping
	0,														// tp_hash
	0,														// tp_call
	0,														// tp_str
	0,														// tp_getattro
	0,														// tp_setattro
	0,														// tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,				// tp_flags
	"A wrapper around tadPole CameraComponent.",			// tp_doc
	0,														// tp_traverse
	0,														// tp_clear
	0,														// tp_richcompare
	0,														// tp_weaklistoffset
	0,														// tp_iter
	0,														// tp_iternext
	pyTadPole_CameraComponent_methods,						// tp_methods
	0,														// tp_members
	0,														// tp_getset
	0,														// tp_base
	0,														// tp_dict
	0,														// tp_descr_get
	0,														// tp_descr_set
	0,														// tp_dictoffset
	(initproc)tadPole::pyTadPole_CameraComponent_init,		// tp_init
	0,														// tp_alloc
	tadPole::pyTadPole_CameraComponent_new					// tp_new
};

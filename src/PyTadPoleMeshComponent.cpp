#include "stdafx.h"
#include "PyTadPoleMeshComponent.h"

#include "Exception.h"
#include "MeshComponent.h"

PyObject * tadPole::pyTadPole_MeshComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{
	PyTadPole_MeshComponent * self = (PyTadPole_MeshComponent *)type->tp_alloc(type, 0);
	if (self)
	{
		self->meshComponent = NULL;
	}

	return (PyObject *)self;
}

int tadPole::pyTadPole_MeshComponent_init(PyTadPole_MeshComponent * self, PyObject * args, PyObject * kwargs)
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

void tadPole::pyTadPole_MeshComponent_dealloc(PyTadPole_MeshComponent * self)
{
	if (!self->meshComponent)
	{
		PyErr_SetString(PyExc_ValueError, "MeshComponent does not exist.");
	}

	delete self->meshComponent->getOwner();
}

PyTypeObject pyTadPole_MeshComponent_type =
{
	PyVarObject_HEAD_INIT(NULL, 0)							// Initializes the header
	"MeshComponent",										// tp_name
	sizeof(tadPole::PyTadPole_MeshComponent),				// tp_basicsize
	0,														// tp_itemsize
	(destructor)tadPole::pyTadPole_MeshComponent_dealloc,	// tp_dealloc
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
	"A wrapper around tadPole MeshComponent.",				// tp_doc
	0,														// tp_traverse
	0,														// tp_clear
	0,														// tp_richcompare
	0,														// tp_weaklistoffset
	0,														// tp_iter
	0,														// tp_iternext
	0,														// tp_methods
	0,														// tp_members
	0,														// tp_getset
	0,														// tp_base
	0,														// tp_dict
	0,														// tp_descr_get
	0,														// tp_descr_set
	0,														// tp_dictoffset
	(initproc)tadPole::pyTadPole_MeshComponent_init,		// tp_init
	0,														// tp_alloc
	tadPole::pyTadPole_MeshComponent_new					// tp_new
};

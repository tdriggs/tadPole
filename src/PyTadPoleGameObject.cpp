#include "stdafx.h"
#include "PyTadPoleGameObject.h"

#include "Scene.h"

PyObject * tadPole::pyTadPole_GameObject_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{
	PyTadPole_GameObject * self = (PyTadPole_GameObject *)type->tp_alloc(type, 0);
	if (self)
	{
		self->gameObject = NULL;
	}

	return (PyObject *)self;
}

int tadPole::pyTadPole_GameObject_init(PyTadPole_GameObject * self, PyObject* args, PyObject * kwargs)
{
	char * name;
	char * groupName;
	groupName = NO_GROUP_NAME; 
	if (!(
		(PyTuple_Size(args) == 2 && PyArg_ParseTuple(args, "ss", &groupName, &name)) ||
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &name))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject = SCENE->createGameObject(groupName, name);

	return 0;
}

PyObject * tadPole::pyTadPole_GameObject_str(PyTadPole_GameObject * self)
{
	if (!self->gameObject)
	{
		PyErr_SetString(PyExc_ValueError, "GameObject does not exist.");
	}

	return PyUnicode_FromString(self->gameObject->getName().c_str());
}

void tadPole::pyTadPole_GameObject_dealloc(PyTadPole_GameObject * self)
{
	if (!self->gameObject)
	{
		PyErr_SetString(PyExc_ValueError, "GameObject does not exist.");
	}
	
	SCENE->deleteGameObject(self->gameObject->getName());
}

PyMethodDef pyTadPole_GameObject_methods[] =
{
	//{ "apply", (PyCFunction)mymod_Image_apply, METH_VARARGS, "Applies a (python) function to each pixel." },
	{ NULL, NULL, 0, NULL }
};

PyTypeObject pyTadPole_GameObject_type =
{
	PyVarObject_HEAD_INIT(NULL, 0)							// Initializes the header
	"GameObject",											// tp_name
	sizeof(tadPole::PyTadPole_GameObject),					// tp_basicsize
	0,														// tp_itemsize
	(destructor)tadPole::pyTadPole_GameObject_dealloc,		// tp_dealloc
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
	(reprfunc)tadPole::pyTadPole_GameObject_str,			// tp_str
	0,														// tp_getattro
	0,														// tp_setattro
	0,														// tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,				// tp_flags
	"A wrapper around tadPole GameObject.",					// tp_doc
	0,														// tp_traverse
	0,														// tp_clear
	0,														// tp_richcompare
	0,														// tp_weaklistoffset
	0,														// tp_iter
	0,														// tp_iternext
	pyTadPole_GameObject_methods,							// tp_methods
	0,														// tp_members
	0,														// tp_getset
	0,														// tp_base
	0,														// tp_dict
	0,														// tp_descr_get
	0,														// tp_descr_set
	0,														// tp_dictoffset
	(initproc)tadPole::pyTadPole_GameObject_init,			// tp_init
	0,														// tp_alloc
	tadPole::pyTadPole_GameObject_new						// tp_new
};

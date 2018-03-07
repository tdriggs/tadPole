#include "stdafx.h"
#include "PyTadPoleLightComponent.h"

#include "Exception.h"
#include "LightComponent.h"

PyObject * tadPole::pyTadPole_LightComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{
	PyTadPole_LightComponent * self = (PyTadPole_LightComponent *)type->tp_alloc(type, 0);
	if (self)
	{
		self->lightComponent = NULL;
	}

	return (PyObject *)self;
}

int tadPole::pyTadPole_LightComponent_init(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs)
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

void tadPole::pyTadPole_LightComponent_dealloc(PyTadPole_LightComponent * self)
{
	if (!self->lightComponent)
	{
		PyErr_SetString(PyExc_ValueError, "LightComponent does not exist.");
	}

	delete self->lightComponent->getOwner();
}

PyObject * tadPole::pyTadPole_LightComponent_setDirection(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs)
{
	float x, y, z;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &x, &y, &z))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->lightComponent->setDirection(glm::vec3(x, y, z));

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_LightComponent_setDiffuseColor(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs)
{
	float r, g, b;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &r, &g, &b))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->lightComponent->setDiffuseColor(r, g, b);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_LightComponent_setSpecularColor(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs)
{
	float r, g, b;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &r, &g, &b))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->lightComponent->setSpecularColor(r, g, b);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_LightComponent_setSpotlightAngles(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs)
{
	float n, f;
	if (!(
		(PyTuple_Size(args) == 2 && PyArg_ParseTuple(args, "ff", &n, &f))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->lightComponent->setSpotlightAngles(n, f);

	Py_RETURN_NONE;
}

PyMethodDef pyTadPole_LightComponent_methods[] =
{
	{ "setDirection", (PyCFunction)tadPole::pyTadPole_LightComponent_setDirection, METH_VARARGS, "" },
	{ "setDiffuseColor", (PyCFunction)tadPole::pyTadPole_LightComponent_setDiffuseColor, METH_VARARGS, "" },
	{ "setSpecularColor", (PyCFunction)tadPole::pyTadPole_LightComponent_setSpecularColor, METH_VARARGS, "" },
	{ "setSpotlightAngles", (PyCFunction)tadPole::pyTadPole_LightComponent_setSpotlightAngles, METH_VARARGS, "" },
	{ NULL, NULL, 0, NULL }
};

PyTypeObject pyTadPole_LightComponent_type =
{
	PyVarObject_HEAD_INIT(NULL, 0)							// Initializes the header
	"LightComponent",										// tp_name
	sizeof(tadPole::PyTadPole_LightComponent),				// tp_basicsize
	0,														// tp_itemsize
	(destructor)tadPole::pyTadPole_LightComponent_dealloc,	// tp_dealloc
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
	"A wrapper around tadPole LightComponent.",				// tp_doc
	0,														// tp_traverse
	0,														// tp_clear
	0,														// tp_richcompare
	0,														// tp_weaklistoffset
	0,														// tp_iter
	0,														// tp_iternext
	pyTadPole_LightComponent_methods,						// tp_methods
	0,														// tp_members
	0,														// tp_getset
	0,														// tp_base
	0,														// tp_dict
	0,														// tp_descr_get
	0,														// tp_descr_set
	0,														// tp_dictoffset
	(initproc)tadPole::pyTadPole_LightComponent_init,		// tp_init
	0,														// tp_alloc
	tadPole::pyTadPole_LightComponent_new					// tp_new
};

#include "stdafx.h"
#include "PyTadPoleScriptComponent.h"

#include "Exception.h"
#include "Scene.h"
#include "PythonScriptComponent.h"
#include "PythonScriptManager.h"

PyObject * tadPole::pyTadPole_ScriptComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{
	PyTadPole_ScriptComponent * self = (PyTadPole_ScriptComponent *)type->tp_alloc(type, 0);
	if (self)
	{
		self->scriptComponent = NULL;
	}

	return (PyObject *)self;
}

int tadPole::pyTadPole_ScriptComponent_init(PyTadPole_ScriptComponent * self, PyObject * args, PyObject * kwargs)
{
	char * name = "";
	char * groupName = NO_GROUP_NAME;
	if (!(
		(PyTuple_Size(args) == 2 && PyArg_ParseTuple(args, "ss", &groupName, &name)) ||
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	if (name != "")
	{
		GameObject * gameObject = SCENE->createGameObject(groupName, name);
		PYTHON_SCRIPT_MANAGER->createPythonGameObject(gameObject);

		std::string className = ((PyObject *)self)->ob_type->tp_name;
		std::string scriptName = className.substr(className.find_last_of(".") + 1, className.size()) + ".py";

		PythonScriptComponent * scriptComponent = gameObject->createPythonScriptComponent(scriptName);
		self->scriptComponent = scriptComponent;
		scriptComponent->setPyObject(self);
		Py_INCREF(self);

		scriptComponent->executeCallback("OnStart");
	}

	return 0;
}

PyObject * tadPole::pyTadPole_ScriptComponent_str(PyTadPole_ScriptComponent * self)
{
	if (!self->scriptComponent)
	{
		PyErr_SetString(PyExc_ValueError, "PythonScriptComponent does not exist.");
	}

	return PyUnicode_FromString(self->scriptComponent->getScriptName().c_str());
}

void tadPole::pyTadPole_ScriptComponent_dealloc(PyTadPole_ScriptComponent * self)
{
	if (!self->scriptComponent)
	{
		PyErr_SetString(PyExc_ValueError, "PythonScriptComponent does not exist.");
	}

	delete self->scriptComponent->getOwner();
}

PyObject * tadPole::pyTadPole_ScriptComponent_getGameObject(PyTadPole_ScriptComponent * self, PyObject * args, PyObject * kwargs)
{
	PyObject * result = (PyObject *)self->scriptComponent->getOwner()->getPyObject();
	Py_INCREF(result);
	return result;
}

PyMethodDef pyTadPole_ScriptComponent_methods[] =
{
	{ "getGameObject", (PyCFunction)tadPole::pyTadPole_ScriptComponent_getGameObject, METH_VARARGS, "" },
	{ NULL, NULL, 0, NULL }
};

PyTypeObject pyTadPole_ScriptComponent_type =
{
	PyVarObject_HEAD_INIT(NULL, 0)							// Initializes the header
	"ScriptComponent",										// tp_name
	sizeof(tadPole::PyTadPole_ScriptComponent),				// tp_basicsize
	0,														// tp_itemsize
	(destructor)tadPole::pyTadPole_ScriptComponent_dealloc,	// tp_dealloc
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
	(reprfunc)tadPole::pyTadPole_ScriptComponent_str,		// tp_str
	0,														// tp_getattro
	0,														// tp_setattro
	0,														// tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,				// tp_flags
	"A wrapper around tadPole ScriptComponent.",			// tp_doc
	0,														// tp_traverse
	0,														// tp_clear
	0,														// tp_richcompare
	0,														// tp_weaklistoffset
	0,														// tp_iter
	0,														// tp_iternext
	pyTadPole_ScriptComponent_methods,						// tp_methods
	0,														// tp_members
	0,														// tp_getset
	0,														// tp_base
	0,														// tp_dict
	0,														// tp_descr_get
	0,														// tp_descr_set
	0,														// tp_dictoffset
	(initproc)tadPole::pyTadPole_ScriptComponent_init,		// tp_init
	0,														// tp_alloc
	tadPole::pyTadPole_ScriptComponent_new					// tp_new
};

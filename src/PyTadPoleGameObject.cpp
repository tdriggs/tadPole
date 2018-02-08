#include "stdafx.h"
#include "PyTadPoleGameObject.h"

#include "Scene.h"
#include "GameObject.h"

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
	name = "";
	groupName = NO_GROUP_NAME; 
	if (!(
		(PyTuple_Size(args) == 2 && PyArg_ParseTuple(args, "ss", &groupName, &name)) ||
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &name)) ||
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	if (name != "")
	{
		self->gameObject = SCENE->createGameObject(groupName, name);
		self->gameObject->setPyObject(self);
		Py_INCREF(self);
	}

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

PyObject * tadPole::pyTadPole_GameObject_createMeshComponent(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	char * fileName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &fileName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	tadPole::MeshComponent * meshComponent = self->gameObject->createMeshComponent(fileName);

	// Eventually return reference to MeshComponent as PyObject *
	Py_RETURN_NONE;
}

/*PyObject * tadPole::pyTadPole_GameObject_createCameraComponent(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	
}*/

/*PyObject * tadPole::pyTadPole_GameObject_createLightComponent(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	
}*/

PyObject * tadPole::pyTadPole_GameObject_getName(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	std::string name = self->gameObject->getName();

	return PyUnicode_FromString(name.c_str());
}

/*PyObject * tadPole::pyTadPole_GameObject_getComponentCount(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{

}*/

PyObject * tadPole::pyTadPole_GameObject_getLocalPosition(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	glm::vec3 position = self->gameObject->getLocalPosition();
	PyObject * result = PyTuple_New(3);

	PyTuple_SetItem(result, 0, PyFloat_FromDouble(position.x));
	PyTuple_SetItem(result, 1, PyFloat_FromDouble(position.y));
	PyTuple_SetItem(result, 2, PyFloat_FromDouble(position.z));

	return result;
}

PyObject * tadPole::pyTadPole_GameObject_getWorldPosition(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	glm::vec3 position = self->gameObject->getWorldPosition();
	PyObject * result = PyTuple_New(3);

	PyTuple_SetItem(result, 0, PyFloat_FromDouble(position.x));
	PyTuple_SetItem(result, 1, PyFloat_FromDouble(position.y));
	PyTuple_SetItem(result, 2, PyFloat_FromDouble(position.z));

	return result;
}

PyObject * tadPole::pyTadPole_GameObject_getLocalOrientation(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	glm::quat orientation = self->gameObject->getLocalOrientation();
	PyObject * result = PyTuple_New(4);

	PyTuple_SetItem(result, 0, PyFloat_FromDouble(orientation.x));
	PyTuple_SetItem(result, 1, PyFloat_FromDouble(orientation.y));
	PyTuple_SetItem(result, 2, PyFloat_FromDouble(orientation.z));
	PyTuple_SetItem(result, 3, PyFloat_FromDouble(orientation.w));

	return result;
}

PyObject * tadPole::pyTadPole_GameObject_getWorldOrientation(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	glm::quat orientation = self->gameObject->getLocalOrientation();
	PyObject * result = PyTuple_New(4);

	PyTuple_SetItem(result, 0, PyFloat_FromDouble(orientation.x));
	PyTuple_SetItem(result, 1, PyFloat_FromDouble(orientation.y));
	PyTuple_SetItem(result, 2, PyFloat_FromDouble(orientation.z));
	PyTuple_SetItem(result, 3, PyFloat_FromDouble(orientation.w));

	return result;
}

PyObject * tadPole::pyTadPole_GameObject_getLocalScale(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	glm::vec3 scale = self->gameObject->getWorldPosition();
	PyObject * result = PyTuple_New(3);

	PyTuple_SetItem(result, 0, PyFloat_FromDouble(scale.x));
	PyTuple_SetItem(result, 1, PyFloat_FromDouble(scale.y));
	PyTuple_SetItem(result, 2, PyFloat_FromDouble(scale.z));

	return result;
}

PyObject * tadPole::pyTadPole_GameObject_getWorldScale(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	glm::vec3 scale = self->gameObject->getWorldPosition();
	PyObject * result = PyTuple_New(3);

	PyTuple_SetItem(result, 0, PyFloat_FromDouble(scale.x));
	PyTuple_SetItem(result, 1, PyFloat_FromDouble(scale.y));
	PyTuple_SetItem(result, 2, PyFloat_FromDouble(scale.z));

	return result;
}

PyObject * tadPole::pyTadPole_GameObject_setActive(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	bool active;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "b", &active))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->setActive(active);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_setParent(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	PyObject * gameObject;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "O", &gameObject))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->setParent(((tadPole::PyTadPole_GameObject *)gameObject)->gameObject);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_setParentInPlace(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	PyObject * gameObject;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "O", &gameObject))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->setParent(((tadPole::PyTadPole_GameObject *)gameObject)->gameObject);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_setPosition(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float x, y, z;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &x, &y, &z))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->setPosition(x, y, z);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_setOrientation(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float axisX, axisY, axisZ, degrees;
	if (!(
		(PyTuple_Size(args) == 4 && PyArg_ParseTuple(args, "ffff", &axisX, &axisY, &axisZ, &degrees))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->setOrientation(axisX, axisY, axisZ, degrees);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_setScale(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float x, y, z;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &x, &y, &z))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->setScale(x, y, z);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_translateLocal(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float x, y, z;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &x, &y, &z))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->translateLocal(x, y, z);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_translateWorld(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float x, y, z;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &x, &y, &z))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->translateWorld(x, y, z);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_rotateLocal(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float axisX, axisY, axisZ, degrees;
	if (!(
		(PyTuple_Size(args) == 4 && PyArg_ParseTuple(args, "ffff", &axisX, &axisY, &axisZ, &degrees))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->rotateLocal(axisX, axisY, axisZ, degrees);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_rotateWorld(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float axisX, axisY, axisZ, degrees;
	if (!(
		(PyTuple_Size(args) == 4 && PyArg_ParseTuple(args, "ffff", &axisX, &axisY, &axisZ, &degrees))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->rotateWorld(axisX, axisY, axisZ, degrees);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_GameObject_scale(tadPole::PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs)
{
	float x, y, z;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &x, &y, &z))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	self->gameObject->scale(x, y, z);

	Py_RETURN_NONE;
}

PyMethodDef pyTadPole_GameObject_methods[] =
{
	{ "createMeshComponent", (PyCFunction)tadPole::pyTadPole_GameObject_createMeshComponent, METH_VARARGS, "" },
	//{ "createCameraComponent", (PyCFunction)tadPole::pyTadPole_GameObject_createCameraComponent, METH_VARARGS, "" },
	//{ "createLightComponent", (PyCFunction)tadPole::pyTadPole_GameObject_createLightComponent, METH_VARARGS, "" },
	{ "getName", (PyCFunction)tadPole::pyTadPole_GameObject_getName, METH_VARARGS, "" },
	//{ "getComponentCount", (PyCFunction)tadPole::pyTadPole_GameObject_getComponentCount, METH_VARARGS, "" },
	{ "getLocalPosition", (PyCFunction)tadPole::pyTadPole_GameObject_getLocalPosition, METH_VARARGS, "" },
	{ "getWorldPosition", (PyCFunction)tadPole::pyTadPole_GameObject_getWorldPosition, METH_VARARGS, "" },
	{ "getLocalOrientation", (PyCFunction)tadPole::pyTadPole_GameObject_getLocalOrientation, METH_VARARGS, "" },
	{ "getWorldOrientation", (PyCFunction)tadPole::pyTadPole_GameObject_getWorldOrientation, METH_VARARGS, "" },
	{ "getLocalScale", (PyCFunction)tadPole::pyTadPole_GameObject_getLocalScale, METH_VARARGS, "" },
	{ "getWorldScale", (PyCFunction)tadPole::pyTadPole_GameObject_getWorldScale, METH_VARARGS, "" },
	{ "setActive", (PyCFunction)tadPole::pyTadPole_GameObject_setActive, METH_VARARGS, "" },
	{ "setParent", (PyCFunction)tadPole::pyTadPole_GameObject_setParent, METH_VARARGS, "" },
	{ "setParentInPlace", (PyCFunction)tadPole::pyTadPole_GameObject_setParentInPlace, METH_VARARGS, "" },
	{ "setPosition", (PyCFunction)tadPole::pyTadPole_GameObject_setPosition, METH_VARARGS, "" },
	{ "setOrientation", (PyCFunction)tadPole::pyTadPole_GameObject_setOrientation, METH_VARARGS, "" },
	{ "setScale", (PyCFunction)tadPole::pyTadPole_GameObject_setScale, METH_VARARGS, "" },
	{ "translateLocal", (PyCFunction)tadPole::pyTadPole_GameObject_translateLocal, METH_VARARGS, "" },
	{ "translateWorld", (PyCFunction)tadPole::pyTadPole_GameObject_translateWorld, METH_VARARGS, "" },
	{ "rotateLocal", (PyCFunction)tadPole::pyTadPole_GameObject_rotateLocal, METH_VARARGS, "" },
	{ "rotateWorld", (PyCFunction)tadPole::pyTadPole_GameObject_rotateWorld, METH_VARARGS, "" },
	{ "scale", (PyCFunction)tadPole::pyTadPole_GameObject_scale, METH_VARARGS, "" },
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

#ifndef PY_TADPOLE_GAME_OBJECT
#define PY_TADPOLE_GAME_OBJECT

#include "stdafx.h"

namespace tadPole
{
	class GameObject;

	typedef struct
	{
		PyObject_HEAD;
		GameObject * gameObject;
	} PyTadPole_GameObject;

	PyObject * pyTadPole_GameObject_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

	int pyTadPole_GameObject_init(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_str(PyTadPole_GameObject * self);

	void pyTadPole_GameObject_dealloc(PyTadPole_GameObject * self);

	PyObject * pyTadPole_GameObject_createMeshComponent(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	//PyObject * pyTadPole_GameObject_createCameraComponent(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	//PyObject * pyTadPole_GameObject_createLightComponent(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getName(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	//PyObject * pyTadPole_GameObject_getComponentCount(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getLocalPosition(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getWorldPosition(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getLocalOrientation(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getWorldOrientation(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getLocalScale(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_getWorldScale(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_setActive(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_setParent(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_setParentInPlace(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_setPosition(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_setOrientation(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_setScale(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_translateLocal(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_translateWorld(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_rotateLocal(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_rotateWorld(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_GameObject_scale(PyTadPole_GameObject * self, PyObject * args, PyObject * kwargs);
}

#endif
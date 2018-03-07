#ifndef PY_TADPOLE_CAMERA_COMPONENT
#define PY_TADPOLE_CAMERA_COMPONENT

#include "stdafx.h"

namespace tadPole
{
	class CameraComponent;

	typedef struct
	{
		PyObject_HEAD;
		CameraComponent * cameraComponent;
	} PyTadPole_CameraComponent;

	PyObject * pyTadPole_CameraComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

	int pyTadPole_CameraComponent_init(PyTadPole_CameraComponent * self, PyObject * args, PyObject * kwargs);

	void pyTadPole_CameraComponent_dealloc(PyTadPole_CameraComponent * self);

	PyObject * pyTadPole_CameraComponent_setClipDistances(PyTadPole_CameraComponent * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_CameraComponent_setViewport(PyTadPole_CameraComponent * self, PyObject * args, PyObject * kwargs);
}

#endif

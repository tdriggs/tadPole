#ifndef PY_TADPOLE_LIGHT_COMPONENT
#define PY_TADPOLE_LIGHT_COMPONENT

#include "stdafx.h"

namespace tadPole
{
	class LightComponent;

	typedef struct
	{
		PyObject_HEAD;
		LightComponent * lightComponent;
	} PyTadPole_LightComponent;

	PyObject * pyTadPole_LightComponent_new(PyTypeObject * type, PyObject * args, PyObject * kwargs);

	int pyTadPole_LightComponent_init(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs);

	void pyTadPole_LightComponent_dealloc(PyTadPole_LightComponent * self);

	PyObject * pyTadPole_LightComponent_setDirection(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_LightComponent_setDiffuseColor(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_LightComponent_setSpecularColor(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs);

	PyObject * pyTadPole_LightComponent_setSpotlightAngles(PyTadPole_LightComponent * self, PyObject * args, PyObject * kwargs);
}

#endif

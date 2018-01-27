#include "stdafx.h"
#include "PyTadPoleModule.h"

#include "PyTadPoleFunctions.h"

PyMethodDef pyTadPoleModuleFunctions[] =
{
	{ "log", tadPole::pyTadPole_log, METH_VARARGS, "Logs a message through LogManager." },
	{ NULL, NULL, 0, NULL }
};

struct PyModuleDef pyTadPoleModule =
{
	PyModuleDef_HEAD_INIT,
	"pyTadPole",
	"A simple game engine for simple games.",
	-1,
	pyTadPoleModuleFunctions
};

PyMODINIT_FUNC tadPole::PyInit_tadPole()
{
	PyObject * mod = PyModule_Create(&(pyTadPoleModule));
	if (mod == NULL)
	{
		return NULL;
	}

	return mod;
}

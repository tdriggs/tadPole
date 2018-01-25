#include "stdafx.h"
#include "PyTadPole.h"


/**
*
*/
struct PyModuleDef moduleDefinition =
{
	PyModuleDef_HEAD_INIT,
	"tadPole",
	"A simple game engine for simple games.",
	-1,
	NULL
};


PyMODINIT_FUNC tadPole::PyInit_tadPole()
{
	PyObject * mod = PyModule_Create(&(moduleDefinition));
	if (mod == NULL)
	{
		return NULL;
	}

	return mod;
}

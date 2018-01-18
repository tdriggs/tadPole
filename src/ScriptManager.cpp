#include "..\include\ScriptManager.h"

PyMODINIT_FUNC tadPole::PyInit_tadPole(void)
{
	PyObject * mod = PyModule_Create(&(tadPole::moduleDefinition));
	if (mod == NULL)
		return NULL;

	return mod;
}

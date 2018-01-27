#include "stdafx.h"
#include "PyTadPoleFunctions.h"

#include "LogManager.h"

PyObject * tadPole::pyTadPole_log(PyObject * self, PyObject * args)
{
	char * message;
	if (!PyArg_ParseTuple(args, "s", &message))
	{
		PyErr_BadArgument();
		return NULL;
	}

	LOG_MANAGER->log(message);
	Py_RETURN_NONE;
}

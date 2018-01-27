#include "stdafx.h"
#include "PythonScriptManager.h"

#include "PyTadPoleModule.h"
#include "LogManager.h"
#include "Exception.h"

tadPole::PythonScriptManager::PythonScriptManager()
{
	PyImport_AppendInittab("pyTadPole", &tadPole::PyInit_tadPole);	Py_Initialize();
}

tadPole::PythonScriptManager::~PythonScriptManager()
{
	Py_Finalize();
}

void tadPole::PythonScriptManager::executeScript(std::string scriptName)
{
	std::ifstream infile;
	std::stringstream textBuffer;
	infile.open(scriptName);
	textBuffer << infile.rdbuf();
	std::string fileText = textBuffer.str();

	PyObject * byteCode = Py_CompileString(fileText.c_str(), scriptName.c_str(), Py_file_input);
	PyObject * module = PyImport_ExecCodeModule(scriptName.c_str(), byteCode);
	
	if (PyErr_Occurred()) {
		PyObject * type, * value, * traceback;
		PyErr_Fetch(&type, &value, &traceback);
		PyErr_NormalizeException(&type, &value, &traceback);

		if (traceback)
		{
			PyObject * tracebackModule = PyImport_ImportModule("traceback");
			if (!tracebackModule) {
				EXCEPTION("Could not load Python traceback module.");
			}

			PyObject * tracebackInformation = PyObject_CallMethod(tracebackModule, "format_exception", "OOO", type, value, traceback);

			PyObject * newLine = PyUnicode_FromString("\n");
			PyObject * tracebackString = PyUnicode_Join(newLine, tracebackInformation);

			LOG_MANAGER->log(PyUnicode_AsUTF8(tracebackString));

			Py_DECREF(tracebackModule);
			Py_DECREF(tracebackInformation);
			Py_DECREF(newLine);
			Py_DECREF(tracebackString);
		}
		else
		{
			if (type)
			{
				PyObject* stringRepresentation = PyObject_Repr(type);
				LOG_MANAGER->log(PyUnicode_AsUTF8(stringRepresentation));
				Py_DecRef(stringRepresentation);
			}
			if (value)
			{
				PyObject* stringRepresentation = PyObject_Repr(value);
				LOG_MANAGER->log(PyUnicode_AsUTF8(stringRepresentation));
				Py_DecRef(stringRepresentation);
			}
		}

		Py_DecRef(type);
		Py_DecRef(value);
		Py_DecRef(traceback);
	}
}

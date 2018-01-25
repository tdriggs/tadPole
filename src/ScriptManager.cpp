#include "stdafx.h"
#include "ScriptManager.h"

#include "PyTadPole.h"

extern struct PyModuleDef moduleDefinition;

tadPole::ScriptManager::ScriptManager()
{
	PyImport_AppendInittab("tadPole", &tadPole::PyInit_tadPole);	Py_Initialize();
}

tadPole::ScriptManager::~ScriptManager()
{
	Py_Finalize();
}

void tadPole::ScriptManager::executeScript(std::string scriptName)
{

}

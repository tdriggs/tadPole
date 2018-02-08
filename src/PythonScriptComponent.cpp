#include "stdafx.h"
#include "PythonScriptComponent.h"

#include "PythonScriptManager.h"
#include "Exception.h"
#include "LogManager.h"

tadPole::PythonScriptComponent::PythonScriptComponent(GameObject * g, std::string scriptName) : Component(g)
{
	this->scriptName = scriptName;
	this->active = true;
	this->className = scriptName.substr(0, scriptName.find_first_of("."));
	this->tadPoleModule = PyImport_ImportModule("pyTadPole");
}

tadPole::PythonScriptComponent::~PythonScriptComponent()
{
}

void tadPole::PythonScriptComponent::update(float deltaTime)
{
	this->executeCallback("OnUpdate");	
}

void tadPole::PythonScriptComponent::setActive(bool active)
{
	this->active = active;
}

tadPole::ComponentType tadPole::PythonScriptComponent::getType()
{
	return ComponentType::SCRIPT;
}

std::string tadPole::PythonScriptComponent::serialize()
{
	std::ostringstream result;

	result << "{\n\t\t\t\t\t\t\t\"type\": \"" << "SCRIPT" << "\",\n\t\t\t\t\t\t\t\"scriptName\": \"" << this->scriptName << "\"\n\t\t\t\t\t\t}";

	return result.str();
}

std::string tadPole::PythonScriptComponent::getScriptName()
{
	return this->scriptName;
}

std::string tadPole::PythonScriptComponent::getClassName()
{
	return this->className;
}

PyObject * tadPole::PythonScriptComponent::getModule()
{
	return this->tadPoleModule;
}

void tadPole::PythonScriptComponent::setPyObject(PyObject * pyObject)
{
	this->pyObject = pyObject;
}

void tadPole::PythonScriptComponent::executeCallback(std::string callbackName)
{
	if (PyObject_HasAttrString(this->pyObject, callbackName.c_str()))
	{
		PyObject * result = PyObject_CallMethodObjArgs((PyObject *)this->pyObject, PyUnicode_FromString(callbackName.c_str()), NULL);

		if (result == NULL)
		{
			if (PyErr_Occurred()) {
				PyObject * type, *value, *traceback;
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
			else
			{
				EXCEPTION("Unknown Python Error Occurred.");
			}
		}
	}
}

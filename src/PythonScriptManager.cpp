#include "stdafx.h"
#include "PythonScriptManager.h"

#include "PyTadPoleModule.h"
#include "LogManager.h"
#include "Exception.h"

extern PyTypeObject pyTadPole_GameObject_type;
extern PyTypeObject pyTadPole_MeshComponent_type;
extern PyTypeObject pyTadPole_CameraComponent_type;
extern PyTypeObject pyTadPole_LightComponent_type;

tadPole::PythonScriptManager::PythonScriptManager()
{
	PyImport_AppendInittab("pyTadPole", &tadPole::PyInit_tadPole);
	Py_Initialize();
}

tadPole::PythonScriptManager::~PythonScriptManager()
{
	Py_Finalize();
}

void tadPole::PythonScriptManager::executeScript(std::string scriptName)
{
	std::ifstream infile;
	std::stringstream textBuffer;
	infile.open(SCRIPT_LOCATION + scriptName);
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

			EXCEPTION(PyUnicode_AsUTF8(tracebackString));

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
				EXCEPTION(PyUnicode_AsUTF8(stringRepresentation));
				Py_DecRef(stringRepresentation);
			}
			if (value)
			{
				PyObject* stringRepresentation = PyObject_Repr(value);
				EXCEPTION(PyUnicode_AsUTF8(stringRepresentation));
				Py_DecRef(stringRepresentation);
			}
		}

		Py_DecRef(type);
		Py_DecRef(value);
		Py_DecRef(traceback);
	}
}

void tadPole::PythonScriptManager::createPythonGameObject(tadPole::GameObject * gameObject)
{
	PyObject * pyObject = PyObject_CallObject((PyObject *)(&pyTadPole_GameObject_type), NULL);
	PyTadPole_GameObject * result = (PyTadPole_GameObject *)pyObject;
	Py_INCREF(result);

	result->gameObject = gameObject;
	gameObject->setPyObject(result);
}

void tadPole::PythonScriptManager::createPythonScriptComponent(PythonScriptComponent * scriptComponent)
{
	PYTHON_SCRIPT_MANAGER->executeScript(scriptComponent->getScriptName());
	if (!PyObject_HasAttrString(scriptComponent->getModule(), scriptComponent->getClassName().c_str()))
	{
		EXCEPTION("Python class does not exist: " + scriptComponent->getClassName());
	}

	PyObject * cls = PyObject_GetAttrString(scriptComponent->getModule(), scriptComponent->getClassName().c_str());
	PyObject * result = PyObject_CallObject(cls, NULL);
	Py_INCREF(result);

	((PyTadPole_ScriptComponent *)result)->scriptComponent = scriptComponent;
	scriptComponent->setPyObject((PyTadPole_ScriptComponent *)result);
}

void tadPole::PythonScriptManager::createPythonMeshComponent(MeshComponent * meshComponent)
{
	PyObject * pyObject = PyObject_CallObject((PyObject *)(&pyTadPole_MeshComponent_type), NULL);
	PyTadPole_MeshComponent * result = (PyTadPole_MeshComponent *)pyObject;
	Py_INCREF(result);

	result->meshComponent = meshComponent;
	meshComponent->setPyObject(result);
}

void tadPole::PythonScriptManager::createPythonCameraComponent(CameraComponent * cameraComponent)
{
	PyObject * pyObject = PyObject_CallObject((PyObject *)(&pyTadPole_CameraComponent_type), NULL);
	PyTadPole_CameraComponent * result = (PyTadPole_CameraComponent *)pyObject;
	Py_INCREF(result);

	result->cameraComponent = cameraComponent;
	cameraComponent->setPyObject(result);
}

void tadPole::PythonScriptManager::createPythonLightComponent(LightComponent * lightComponent)
{
	PyObject * pyObject = PyObject_CallObject((PyObject *)(&pyTadPole_LightComponent_type), NULL);
	PyTadPole_LightComponent * result = (PyTadPole_LightComponent *)pyObject;
	Py_INCREF(result);

	result->lightComponent = lightComponent;
	lightComponent->setPyObject(result);
}

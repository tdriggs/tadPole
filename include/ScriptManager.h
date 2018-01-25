#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define SCRIPT_MANAGER tadPole::ScriptManager::getInstance()	///< Convnenience macro for access to the singleton instance.

namespace tadPole
{
	/**
	* 
	*/
	class ScriptManager : public Singleton<ScriptManager>
	{
		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* ScriptManager constructor.
		*/
		ScriptManager();

		/**
		* ScriptManager destructor.
		*/
		~ScriptManager();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Executes a Python script.
		*/
		void executeScript(std::string scriptName);
	};
}

#endif

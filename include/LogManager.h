#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define LOG_MANAGER tadPole::LogManager::getInstance()	///< Convienience macro for the singleton instance.
#define LOG_FILE_PATH "tadPole_log.txt"					///< The name of the file to output the log.

namespace tadPole
{
	/**
	* Log events and exceptions that tadPole outputs.
	*/
	class LogManager : public Singleton<LogManager>
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		std::ofstream logFile;					///< The file to which to output the log.
		std::vector<std::string> logHistory;	///< The history of what has been written to the log.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* LogManager constructor.
		*/
		LogManager();

		/**
		* LogManager destructor.
		*/
		~LogManager();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Write a message to the log and display it to the DebugOverlay.
		*/
		void log(std::string message);
	};
}

#endif

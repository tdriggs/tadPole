#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"

#define LOG_MANAGER tadPole::LogManager::getInstance()
#define LOG_FILE_PATH "tadPole_log.txt"

namespace tadPole
{
	class LogManager : public Singleton<LogManager>
	{
	protected:
		std::ofstream logFile;
		std::vector<std::string> logHistory;

	public:
		LogManager();
		~LogManager();

		void log(std::string message);
	};
}

#endif

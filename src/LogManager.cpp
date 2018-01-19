#include "stdafx.h"
#include "LogManager.h"

#include <ctime>
#include "DebugOverlay.h"

tadPole::LogManager::LogManager() : Singleton<LogManager>()
{
	this->logFile.open(LOG_FILE_PATH);
}

tadPole::LogManager::~LogManager()
{
	this->logFile.close();
}

void tadPole::LogManager::log(std::string message)
{
	DEBUG_OVERLAY->postMessage(message);

	time_t rawtime;
	time(&rawtime);
	char buffer[256];
	#pragma warning(disable: 4996)
	strftime(buffer, sizeof(buffer), "[%m/%d/%Y@%I:%M:%S]  ", localtime(&rawtime));

	std::string formatted_time(buffer);

	this->logFile << formatted_time << message << '\n';
	this->logFile.flush();
}

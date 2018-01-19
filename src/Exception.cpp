#include "stdafx.h"
#include "Exception.h"

#include "LogManager.h"

tadPole::Exception::Exception(std::string message, std::string fileName, int lineNumber)
{
	this->message = message;
	this->fileName = fileName.substr(fileName.find_last_of('\\') + 1, fileName.length());
	this->lineNumber = lineNumber;
}

void tadPole::Exception::logException()
{
	char formattedMessage[1024];
	sprintf(formattedMessage, "[%s: %d] %s", this->fileName.c_str(), this->lineNumber, this->message.c_str());
	LOG_MANAGER->log((std::string)formattedMessage);
}

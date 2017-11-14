#include "stdafx.h"
#include "Exception.h"

#include "LogManager.h"

tadPole::Exception::Exception(std::string message, std::string fname, int lnum)
{
	this->message = message;
	this->fname = fname.substr(fname.find_last_of('\\') + 1, fname.length());
	this->lnum = lnum;
}

void tadPole::Exception::logException()
{
	char formattedMessage[1024];
	sprintf(formattedMessage, "[%s: %d] %s", this->fname.c_str(), this->lnum, this->message.c_str());
	LOG_MANAGER->log((std::string)formattedMessage);
}

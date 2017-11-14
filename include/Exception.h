#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "stdafx.h"

#define EXCEPTION(msg) throw tadPole::Exception(msg, __FILE__, __LINE__)

namespace tadPole
{
	class Exception
	{
	protected:
		 std::string message;
		 std::string fname;
		 int lnum;

	public:
		Exception(std::string message, std::string fname, int lnum);
		void logException();

	};
}

#endif

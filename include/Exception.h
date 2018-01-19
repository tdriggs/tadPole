#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "stdafx.h"

#define EXCEPTION(msg) throw tadPole::Exception(msg, __FILE__, __LINE__)	///< Convienience macro for throwing an Exception.

namespace tadPole
{
	/**
	* A class that contains debug information handles the logging and throwing of an exception.
	*/
	class Exception
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		 std::string message;	///< The message to be displayed when this Exception is thrown.
		 std::string fileName;	///< The name of the file that threw this Exception.
		 int lineNumber;		///< The line number on which this Exception was thrown.


		 // @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Exception constructor.
		*/
		Exception(
			std::string message,	///< The message to be displayed when this Exception is thrown.
			std::string fileName,	///< The name of the file that threw this Exception.
			int lineNumber			///< The line number on which this Exception was thrown.
		);


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Log this Exception with LogManager.
		*/
		void logException();

	};
}

#endif

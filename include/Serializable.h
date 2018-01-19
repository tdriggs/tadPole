#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "stdafx.h"

#include <string>

namespace tadPole
{
	/**
	* An interface in spirit that requires children classes to be able to be 
	* serialized into JSON for saving to a file.
	*/
	class Serializable
	{
		// @@@@@ VIRTUAL METHODS @@@@@
	public:
		/**
		* Turn this object into a std::string of valid, formatted JSON.
		*/
		virtual std::string serialize() = 0;
	};
}

#endif

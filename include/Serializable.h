#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "stdafx.h"

#include <string>

namespace tadPole
{
	class Serializable
	{
		virtual std::string serialize() = 0;
	};
}

#endif

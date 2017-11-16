#ifndef T_MATH_H
#define T_MATH_H

#include "stdafx.h"

namespace tadPole
{
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
		~Vector3() { }
	};
}

#endif

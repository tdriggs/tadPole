#ifndef SINGLETON_H
#define SINGLETON_H

#include "stdafx.h"

namespace tadPole
{
	template<class T>
	class Singleton
	{
	protected:
		static T * instance;
		
	public:
		Singleton() 
		{
			if (instance == NULL)
			{
				this->instance = (T *)this;
			}
		}

		~Singleton()
		{
			delete this->instance;
		}

		static T * getInstance() 
		{
			return (T *)T::instance;
		}
	};
}

#endif

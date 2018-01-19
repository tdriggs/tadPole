#ifndef SINGLETON_H
#define SINGLETON_H

#include "stdafx.h"

namespace tadPole
{
	/**
	* A class to provide singleton functionality. Singleton classes must be declared in Singleton.cpp
	* in order to work properly and must be instantiated at least once, although the reference does
	* not need to be saved.
	*/
	template<class T>
	class Singleton
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		static T * instance;	///< The singleton instance of this Singleton.
		

		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Singleton constructor.
		*/
		Singleton() 
		{
			if (this->instance == NULL)
			{
				this->instance = (T *)this;
			}
		}

		/**
		* Singleton destructor.
		*/
		~Singleton()
		{
			delete this->instance;
		}


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Get the singleton instance of this Singleton.
		*/
		static T * getInstance() 
		{
			return (T *)T::instance;
		}
	};
}

#endif

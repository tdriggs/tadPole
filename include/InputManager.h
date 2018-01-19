#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"
#include "Keyboard.h"

#define INPUT_MANAGER tadPole::InputManager::getInstance()	///< Convienience macro for the singleton instance.

namespace tadPole
{
	/**
	* A manager that handles all incoming input from the operating system and notifies the parts of tadPole
	* that need to know about that specific input.
	*/
	class InputManager : public Singleton<InputManager>
	{
		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* InputManager constructor.
		*/
		InputManager();

		/**
		* InputManager desturctor.
		*/
		~InputManager();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Handle a key down event.
		*/
		void keyDown(
			Key key		///< The key that was pushed down.
		);

		/**
		* Handle a key up event.
		*/
		void keyUp(
			Key key		///< The key that was released up.
		);
	};
}

#endif

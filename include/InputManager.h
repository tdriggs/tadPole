#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "stdafx.h"

#include "Singleton.h"
#include "Keyboard.h"

#define INPUT_MANAGER tadPole::InputManager::getInstance()

namespace tadPole
{
	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void key_down(Key key);
		void key_up(Key key);
	};
}

#endif

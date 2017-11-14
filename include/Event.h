#ifndef EVENT_H
#define EVENT_H

#include "stdafx.h"

#include "Keyboard.h"

namespace tadPole
{
	typedef int EventType;

	#define EVT_QUIT				 SDL_QUIT
	#define EVT_WINDOW				 SDL_WINDOWEVENT
	#define EVT_SYSTEM				 SDL_SYSWMEVENT
	#define EVT_KEYDOWN				 SDL_KEYDOWN
	#define EVT_KEYUP				 SDL_KEYUP
	#define EVT_TEXTEDITING			 SDL_TEXTEDITING
	#define EVT_TEXTINPUT			 SDL_TEXTINPUT
	#define EVT_KEYMAPCHANGE		 SDL_KEYMAPCHANGED
	#define EVT_MOUSEMOVE			 SDL_MOUSEMOTION
	#define EVT_MOUSEBUTTONDOWN		 SDL_MOUSEBUTTONDOWN
	#define EVT_MOUSEBUTTONUP		 SDL_MOUSEBUTTONUP
	#define EVT_MOUSEWHEEL			 SDL_MOUSEWHEEL
	#define EVT_JOYAXISMOTION		 SDL_JOYAXISMOTION
	#define EVT_JOYBALLMOTION		 SDL_JOYBALLMOTION
	#define EVT_JOYHATMOTION		 SDL_JOYHATMOTION
	#define EVT_JOYBUTTONDOWN		 SDL_JOYBUTTONDOWN
	#define EVT_JOYBUTTONUP			 SDL_JOYBUTTONUP
	#define EVT_JOYDEVICEADDED		 SDL_JOYDEVICEADDED
	#define EVT_JOYDEVICEREMOVED	 SDL_JOYDEVICEREMOVED
	#define EVT_CONTAXISMOTION		 SDL_CONTROLLERAXISMOTION
	#define EVT_CONTBUTTONDOWN		 SDL_CONTROLLERBUTTONDOWN
	#define EVT_CONTBUTTONUP		 SDL_CONTROLLERBUTTONUP
	#define EVT_CONTDEVICEADDED		 SDL_CONTROLLERDEVICEADDED
	#define EVT_CONTDEVICEREMOVED	 SDL_CONTROLLERDEVICEREMOVED
	#define EVT_CONTADEVICECHANGE	 SDL_CONTROLLERDEVICEREMAPPED
	#define EVT_FINGERDOWN			 SDL_FINGERDOWN
	#define EVT_FINGERUP			 SDL_FINGERUP
	#define EVT_FINGERMOVE			 SDL_FINGERMOTION

	class Event
	{
	protected:
		SDL_Event sdlEvent;

	public:
		Event();
		~Event();

		bool poll();
		// wait();
		// waitTimeout();
		// peep();
		// push();
		EventType getType();
		Key getKey();
		// getCommon();
		// getWindow();
		// getTextEdit();
		// getTextInput();
		// getMouseMotion();
		// getMouseButton();
		// getMouseWheel();
		// getJoyAxis();
		// getJoyBall();
		// getJoyHat();
		// getJoyButton();
		// getControllerAxis();
		// getControllerButton();
		// getControllerDevice();
		// getAudioDevice();
		// getQuit();
		// getUser();
		// getSystemWindow();
		// getTouch();
	};
}

#endif

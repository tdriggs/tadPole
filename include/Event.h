#ifndef EVENT_H
#define EVENT_H

#include "stdafx.h"

#include "Keyboard.h"

namespace tadPole
{
	typedef int EventType;	///< The tadPole representation of SDL_EventType.

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

	/**
	* A class that is primarily for handling interrupts and system events and integrating
	* support for those events into tadPole.
	*/
	class Event
	{
		// @@@@@ ATTRIBUTES @@@@@
	protected:
		SDL_Event sdlEvent;	///< The SDL representation of this Event.


		// @@@@@ CONSTRUCTORS / DESTRUCTOR @@@@@
	public:
		/**
		* Event constructor.
		*/
		Event();

		/**
		* Event destructor.
		*/
		~Event();


		// @@@@@ PUBLIC METHODS @@@@@
	public:
		/**
		* Ask the operating system to get the next waiting event.
		*/
		bool poll();

		/**
		* Get the EventType of this Event.
		*/
		EventType getType();

		/**
		* Get the key of this Event. Only applicable if this Event involves
		* a keyboard key.
		*/
		Key getKey();
	};
}

#endif

#include "stdafx.h"
#include "Event.h"

tadPole::Event::Event()
{
	this->sdlEvent = SDL_Event();
}

tadPole::Event::~Event()
{
}

bool tadPole::Event::poll()
{
	return SDL_PollEvent(&this->sdlEvent);
}

tadPole::EventType tadPole::Event::getType()
{
	return (EventType)this->sdlEvent.type;
}

tadPole::Key tadPole::Event::getKey()
{
	return (Key)this->sdlEvent.key.keysym.sym;
}

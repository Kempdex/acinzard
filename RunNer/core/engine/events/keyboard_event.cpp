#include "keyboard_event.h"


using namespace core;

keyboard_event::keyboard_event(int _key, int _scancode, int _action, int _mods)
{
	this->type = EV_KEYBOARD;
	this->key = _key;
	this->scancode = _scancode;
	this->action = _action;
	this->mods = _mods;
}

int core::keyboard_event::get_key()
{
	return this->key;
}

int core::keyboard_event::get_scancode()
{
	return this->scancode;
}

int core::keyboard_event::get_action()
{
	return this->action;
}

int core::keyboard_event::get_mods()
{
	return this->mods;
}

keyboard_event::~keyboard_event()
{
}

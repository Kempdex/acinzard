#pragma once
#include <stdint.h>
#include <engine/events/_event.h>

namespace core {
	class keyboard_event : public _event
	{
		int key;
		int scancode;
		int action;
		int mods;
	public:
		keyboard_event(int _key, int _scancode, int _action, int _mods);
		int get_key();
		int get_scancode();
		int get_action();
		int get_mods();

		~keyboard_event();
	};
}

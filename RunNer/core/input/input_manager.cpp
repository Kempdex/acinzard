#include "input_manager.h"

using namespace core;

input_manager::input_manager()
{
}


input_manager::~input_manager()
{
}

void input_manager::handle_event(_event* ev)
{
	logger::debug(ev->get_type());
	if (ev->get_type() == EV_MOUSE) {
		mouse_event* me = dynamic_cast<mouse_event*>(ev);
		logger::debug(me->get_x_pos(), me->get_y_pos());
	}
	if (ev->get_type() == EV_KEYBOARD) {
		keyboard_event* ke = dynamic_cast<keyboard_event*>(ev);
		logger::debug(ke->get_key(), ke->get_action(), ke->get_scancode(), ke->get_mods());
	}
}

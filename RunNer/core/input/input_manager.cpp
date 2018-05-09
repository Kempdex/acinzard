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
	if (ev->get_type() == EV_MOUSE) {
		mouse_event* me = dynamic_cast<mouse_event*>(ev);
		logger::debug(me->get_x_pos(), me->get_y_pos());
	}
}

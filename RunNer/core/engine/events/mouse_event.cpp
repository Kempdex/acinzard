#include "mouse_event.h"

using namespace core;


mouse_event::mouse_event(double _x, double _y)
{
	this->type = core::EV_MOUSE;
	this->x = _x;
	this->y = _y;
}


mouse_event::~mouse_event()
{
}

double core::mouse_event::get_x_pos()
{
	return this->x;
}

double core::mouse_event::get_y_pos()
{
	return this->y;
}

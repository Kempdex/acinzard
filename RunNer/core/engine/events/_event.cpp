#include "_event.h"

using namespace core;

_event::_event(_event_type _type)
{
	this->type = _type;
}

_event_type core::_event::get_type()
{
	return this->type;
}

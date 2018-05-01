#include "engine_module.h"
#include <engine/events/event_dispatcher.h>

using namespace core;

engine_module::engine_module()
{
}


engine_module::~engine_module()
{
}

void engine_module::raise_event(_event ev)
{
	event_dispatcher::handle_event(ev);
}

void engine_module::start_listen_events_of_type(_event_type _type)
{
	event_dispatcher::subscribe_on_events(_type, this);
}

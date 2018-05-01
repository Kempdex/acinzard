#include "event_dispatcher.h"

using namespace core;

std::map<_event_type, std::vector<engine_module*>> event_dispatcher::_listeners;

void core::event_dispatcher::handle_event(_event ev)
{
	_event_type _type = ev.get_type();
	for (std::vector<engine_module*>::iterator it = _listeners[_type].begin(); it != _listeners[_type].end(); it++) {
		(*it)->handle_event(ev);
	}
}

void core::event_dispatcher::subscribe_on_events(_event_type _type, engine_module * _module)
{
	//Check on unique
	_listeners[_type].push_back(_module);
}


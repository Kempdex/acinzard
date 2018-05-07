#pragma once
#include <engine/events/_event.h>
#include <engine/engine_module.h>

#include <map>
#include <vector>


namespace core {
	class event_dispatcher
	{
		event_dispatcher() {}


		typedef std::vector<core::engine_module*> modules;

		//Every event type has own list of listeners
		static std::map< _event_type, modules > _listeners;
	public:
		
		static void handle_event(_event* ev);

		static void subscribe_on_events(_event_type _type, engine_module* _module);
	};

}
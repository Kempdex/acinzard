#pragma once

#include <engine/events/_event.h>


namespace core {
	class engine_module
	{
	public:
		engine_module();
		virtual ~engine_module();

		virtual void raise_event(_event* ev);
		virtual void start_listen_events_of_type(_event_type _type);
		virtual void handle_event(_event* ev) = 0;
	};

}
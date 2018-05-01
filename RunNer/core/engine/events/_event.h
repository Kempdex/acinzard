#pragma once
#include <engine/events/_event_type.h>

namespace core {
	class _event
	{
		_event_type type;
	public:
		_event(_event_type _type);
		~_event() {}

		_event_type get_type();
	};
}

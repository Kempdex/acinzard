#pragma once
#include <engine/events/_event_type.h>

namespace core {
	class _event
	{
	protected:
		_event_type type;
	public:
		_event();
		virtual ~_event() {}

		_event_type get_type();
	};
}

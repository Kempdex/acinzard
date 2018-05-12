#pragma once
#include <engine/engine_module.h>
#include <engine/events/mouse_event.h>
#include <engine/events/keyboard_event.h>

#include <GLFW\glfw3.h>

#include <util/logger.h>

namespace core {
	class input_manager : public engine_module
	{
		
	public:
		input_manager();
		~input_manager();

		virtual void handle_event(_event* ev);
	};
}

#pragma once
#include <stdint.h>
#include <engine/events/_event.h>

namespace core {
	class mouse_event : public _event
	{
		double x;
		double y;
	public:
		
		mouse_event(double _x, double _y);
		~mouse_event();

		double get_x_pos();
		double get_y_pos();
	};
	
}
#include "camera.h"

using namespace core;

camera::camera(glm::vec3 start_pos, glm::vec3 up, float _mouse_sens, float _mouse_speed)
	: front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	this->position = start_pos;
	this->up = up;
	this->mouse_sens = _mouse_sens;
	this->mouse_speed = _mouse_speed;
}

camera::~camera()
{

}

glm::mat4 core::camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void core::camera::handle_event(_event* ev)
{
	if (ev->get_type() == EV_MOUSE) {
		mouse_event *_me = dynamic_cast<mouse_event*>(ev);
		//logger::debug("X:", _me->get_x_pos(), "Y:", _me->get_y_pos());
		//position = glm::vec3(_me->get_x_pos(), _me->get_y_pos(), 0.0f);
	}
}

void camera::start_listen_events_of_type(_event_type _type)
{
	engine_module::start_listen_events_of_type(_type);
}


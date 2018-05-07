#pragma once
#include <engine/engine_module.h>
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <engine/events/mouse_event.h>

#include <util/logger.h>

namespace core {
	class camera : engine_module
	{
		glm::mat4 view;

		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 target;

		float mouse_sens;
		float mouse_speed;
	public:
		camera(glm::vec3 start_pos, glm::vec3 up, float _mouse_sens, float _mouse_speed);
		~camera();

		glm::mat4 get_view_matrix();

		virtual void handle_event(_event* ev);
		virtual void start_listen_events_of_type(_event_type _type);
	};
}

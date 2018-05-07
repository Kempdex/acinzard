#pragma once
#include <glad/glad.h>
#include <engine/engine_module.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <renderer/window.h>

namespace core {
	class renderer : public engine_module
	{
		
		GLuint box_VBO;

		glm::mat4 projection;

		window *_window;

	public:
		GLuint VAO;
		renderer();
		~renderer();

		void init_renderer(window *win);

		void clear_screen(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		void draw_object(/*Object here*/);

		glm::mat4 get_projection() const;

		virtual void handle_event(_event* ev);
	};
}

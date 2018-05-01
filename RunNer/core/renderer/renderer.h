#pragma once
#include <glad/glad.h>
#include <engine/engine_module.h>

namespace core {
	class renderer : public engine_module
	{
		
		GLuint box_VBO;

	public:
		GLuint VAO;
		renderer();
		~renderer();

		void init_renderer();

		void clear_screen(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		void draw_object(/*Object here*/);

		virtual void handle_event(_event ev);
	};
}

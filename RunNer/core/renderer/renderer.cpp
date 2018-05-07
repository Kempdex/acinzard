#include "renderer.h"

using namespace core;

renderer::renderer()
{

}


renderer::~renderer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->box_VBO);
}

void renderer::init_renderer(window *win)
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->box_VBO);

	glBindVertexArray(VAO);

	GLfloat box_vertices[] = {
		 //Position           //Color              //Texture
		 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, box_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertices), box_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	_window = win;

	projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, (float)_window->get_width(), 0.0f, (float)_window->get_height(), 0.0f, 10.0f);
}

void renderer::clear_screen(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::draw_object()
{

}

glm::mat4 core::renderer::get_projection() const
{
	return this->projection;
}

void renderer::handle_event(_event* ev)
{
	//No imp
}

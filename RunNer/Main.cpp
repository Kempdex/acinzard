#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/window.h>
#include <renderer/shader.h>
#include <renderer/texture.h>
#include <renderer/renderer.h>
#include <renderer/camera.h>
#include <input/input_manager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <util/logger.h>

#include <engine/events/_event.h>
#include <engine/events/mouse_event.h>

#include <ecs/entity/entity.h>

#include <ecs/component/component.h>
#include <ecs/component/components.h>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace core;
using namespace acinzard;

#include <string>
#include <map>

std::map<GLchar, character> characters;

GLuint text_VAO;
GLuint text_VBO;


int main() {
	//Init
	if (!glfwInit()) {
		logger::error("GLFW initialize failed");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window *win = new window("RunNer", 800, 600, false);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		logger::warning("Failed to initialize GLAD");
		return 1;
	}

	logger::debug("OpenGL version: ", glGetString(GL_VERSION));
	glEnable(GL_DEPTH_TEST);

	camera *_camera = new camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 4.5f, 4.5f);
	_camera->start_listen_events_of_type(EV_MOUSE);
	//
	shader *test_shader = new shader("C:/Dev/RunNer/RunNer/res/shaders/main.v", "C:/Dev/RunNer/RunNer/res/shaders/main.f");
	shader *text_shader = new shader("C:/Dev/RunNer/RunNer/res/shaders/text.v", "C:/Dev/RunNer/RunNer/res/shaders/text.f");
	//
	texture *_texture = new texture("C:/Dev/RunNer/RunNer/res/player.jpg");
	//
	renderer *_renderer = new renderer();
	_renderer->init_renderer(win, _camera);
	_renderer->set_default_shader(test_shader);
	_renderer->set_default_texture(_texture);
	_renderer->set_default_text_shader(text_shader);
	_renderer->load_font("C:/Dev/RunNer/RunNer/res/fonts/Andy.ttf", 128);

	//
	input_manager* in_man = new input_manager();
	//in_man->start_listen_events_of_type(EV_MOUSE);
	//in_man->start_listen_events_of_type(EV_KEYBOARD);

	entity *ent = new entity();
	ent->add_component<transform>();
	ent->add_component<sprite>();
	ent->get_component<sprite>().set_transform_component(&ent->get_component<transform>());
	ent->get_component<sprite>().set_shader(test_shader);
	ent->get_component<sprite>().set_texture(_texture);
	ent->get_component<sprite>().set_renderer(_renderer);

	ent->get_component<transform>().translate(glm::vec3(400.0f, 230.0f, 2.0f));
	ent->get_component<transform>().scale(glm::vec3(300.0f, 200.0f, 0.0f));

	double delta_time = 0.0f;
	double last_frame = 0.0f;

	float x = 0.0f;
	float speed = 0.01f;

	while (!glfwWindowShouldClose(win->get_window_ptr())) {
		
		double current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;
		glfwSetWindowTitle(win->get_window_ptr(), std::to_string(delta_time).c_str());

		_renderer->clear_screen(0.1f, 0.1f, 0.1f, 1.0f);

		ent->update();

		//Debug information
		_renderer->draw_text(NULL, std::to_string(delta_time), 25.0f, win->get_height() - 25.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
		_renderer->draw_text(NULL, "This is test text", 500.0f, 500.0f, 0.6f, glm::vec3(0.5f, 0.8f, 0.2f));
		_renderer->draw_text(NULL, "COCK", 300.0f, 300.0f, 4.0f, glm::vec3(1.0f, 0.5f, 0.0f));

		glfwSwapBuffers(win->get_window_ptr());
		glfwPollEvents();
	}

	delete text_shader;
	delete in_man;
	delete ent;
	delete _texture;
	delete test_shader;
	delete _camera;
	delete _renderer;
	delete win;

	glfwTerminate();
	return 0;
}
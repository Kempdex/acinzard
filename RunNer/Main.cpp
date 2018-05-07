#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/window.h>
#include <renderer/shader.h>
#include <renderer/texture.h>
#include <renderer/renderer.h>
#include <renderer/camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <util/logger.h>

#include <engine/events/_event.h>
#include <engine/events/mouse_event.h>

#include <ecs/entity/entity.h>

#include <ecs/component/component.h>
#include <ecs/component/components.h>

using namespace core;
using namespace acinzard;

int main() {

	entity *ent = new entity();
	ent->add_component<transform>();
	ent->get_component<transform>().translate(glm::vec3(1.0f, 1.0f, 1.0f));

	//Init
	if (!glfwInit()) {
		core::logger::error("GLFW initialize failed");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	core::window *win = new core::window("RunNer", 800, 600, false);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		core::logger::warning("Failed to initialize GLAD");
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	core::renderer *_renderer = new core::renderer();
	_renderer->init_renderer(win);

	core::camera *_camera = new core::camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 4.5f, 4.5f);
	_camera->start_listen_events_of_type(core::EV_MOUSE);

	core::shader test_shader("C:/Dev/RunNer/RunNer/res/shaders/main.v", "C:/Dev/RunNer/RunNer/res/shaders/main.f");

	core::texture _texture = core::texture("C:/Dev/RunNer/RunNer/res/player.jpg");

	double delta_time = 0.0f;
	double last_frame = 0.0f;

	while (!glfwWindowShouldClose(win->get_window_ptr())) {

		double current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;
		glfwSetWindowTitle(win->get_window_ptr(), std::to_string(delta_time).c_str());

		_renderer->clear_screen(0.1f, 0.1f, 0.1f, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		_texture.bind();

		test_shader.use();

		glBindVertexArray(_renderer->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 8);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(400.0f, 230.0f, 2.0f));
		model = glm::scale(model, glm::vec3(300.0f, 200.0f, 0.0f));

		glm::mat4 MVP = _renderer->get_projection() * _camera->get_view_matrix() * model;

		test_shader.set_mat4("MVP", MVP);
		glBindVertexArray(_renderer->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 8);

		glfwSwapBuffers(win->get_window_ptr());
		glfwPollEvents();


	}

	delete _camera;
	delete _renderer;
	delete win;
	glfwTerminate();
	return 0;
}
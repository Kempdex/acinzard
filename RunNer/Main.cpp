#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/window.h>
#include <renderer/shader.h>
#include <renderer/texture.h>
#include <renderer/renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* win, int width, int height);

int main() {

	//Init
	if (!glfwInit()) {
		printf("ERROR: GLFW Initialize failed");
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	core::window *win = new core::window("RunNer", 800, 600, false);
	glfwSetFramebufferSizeCallback(win->get_window_ptr(), framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD");
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	core::renderer *_renderer = new core::renderer();
	_renderer->init_renderer();

	core::shader test_shader("C:/Dev/RunNer/RunNer/res/shaders/main.v", "C:/Dev/RunNer/RunNer/res/shaders/main.f");

	core::texture _texture = core::texture("C:/Dev/RunNer/RunNer/res/player.jpg");

	test_shader.use();
	test_shader.set_int("_texture", 0);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, (float)win->get_width(), 0.0f, (float)win->get_height(), 0.0f, 100.0f);

	while (!glfwWindowShouldClose(win->get_window_ptr())) {
		
		_renderer->clear_screen(0.2f, 1.0f, 0.5f, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		_texture.bind();

		test_shader.use();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(400.0f, 230.0f, 2.0f));
		model = glm::scale(model, glm::vec3(200.0f, 200.0f, 0.0f));

		glm::mat4 MVP = projection * view * model;

		//test_shader.set_mat4("view", view);
		//test_shader.set_mat4("model", model);
		test_shader.set_mat4("MVP", MVP);

		glBindVertexArray(_renderer->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 8);

		glfwSwapBuffers(win->get_window_ptr());
		glfwPollEvents();
	}

	delete _renderer;
	delete win;
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* win, int width, int height) {
	glViewport(0, 0, width, height);
}
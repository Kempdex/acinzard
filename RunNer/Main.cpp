#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/window.h>
#include <renderer/shader.h>

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

	core::shader test_shader("C:/Dev/RunNer/RunNer/res/shaders/main.v", "C:/Dev/RunNer/RunNer/res/shaders/main.f");
	
	GLfloat vertices[] = {
		//Position         //Color
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	    1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(win->get_window_ptr())) {
		
		glClearColor(0.2f, 0.5f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		test_shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12);

		glfwSwapBuffers(win->get_window_ptr());
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete win;
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* win, int width, int height) {
	glViewport(0, 0, width, height);
}
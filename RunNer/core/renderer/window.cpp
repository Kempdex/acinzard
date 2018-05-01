#include "window.h"

using namespace core;


window::window()
{
	this->width = DEFAULT_SCREEN_WIDTH;
	this->height = DEFAULT_SCREEN_HEIGHT;
	this->title = DEFAULT_SCREEN_TITLE;

	window_ptr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window_ptr) {
		//Logger 
	}

	glfwMakeContextCurrent(window_ptr);

	glfwSetWindowUserPointer(window_ptr, this);
	glfwSetKeyCallback(window_ptr, key_callback);
}

core::window::window(std::string _title, uint32_t _width, uint32_t _height)
{
	this->width = _width;
	this->height = _height;
	this->title = _title;
	window_ptr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window_ptr) {
		//Logger
	}
	glfwMakeContextCurrent(window_ptr);
	
	glfwSetWindowUserPointer(window_ptr, this);
	glfwSetKeyCallback(window_ptr, key_callback);
}

core::window::window(std::string _title, uint32_t _width, uint32_t _height, bool fullscreen) {
	this->width = _width;
	this->height = _height;
	this->title = _title;
	//                                                          Sheeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeet
	window_ptr = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!window_ptr) {
		//Logger
	}

	glfwMakeContextCurrent(window_ptr);

	glfwSetWindowUserPointer(window_ptr, this);
	glfwSetKeyCallback(window_ptr, key_callback);
	//glfwSetFramebufferSizeCallback(window_ptr, framebuffer_resize_callback);

	glViewport(0, 0, width, height);
}

window::~window()
{
	glfwDestroyWindow(window_ptr);
}

void window::key_callback(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	void *data = glfwGetWindowUserPointer(win);
	window *w = static_cast<window*>(data);

	w->key_event_listener(key, scancode, action, mods);
}

void window::framebuffer_resize_callback(GLFWwindow * win, int width, int height)
{
	glViewport(0, 0, width, height);
}

void core::window::handle_event(_event ev)
{

}

GLFWwindow * core::window::get_window_ptr()
{
	return this->window_ptr;
}

uint32_t core::window::get_width() const
{
	return this->width;
}

uint32_t core::window::get_height() const
{
	return this->height;
}

std::string core::window::get_title() const
{
	return this->title;
}



void window::key_event_listener(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		printf("Key e was pressed");
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window_ptr, true);
	}
}
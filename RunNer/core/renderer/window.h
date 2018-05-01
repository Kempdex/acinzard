#pragma once
#include <stdint.h>
#include <string>
#include <engine/engine_module.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600
#define DEFAULT_SCREEN_TITLE "RunNer"

//GLFW wrapper
namespace core {
	class window : public engine_module
	{
		uint32_t width;
		uint32_t height;
		std::string title;
		GLFWwindow *window_ptr;

		void key_event_listener(int key, int scancode, int action, int mods);
		static void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods);
		void framebuffer_resize_callback(GLFWwindow *win, int width, int height);

	public:
		window();
		window(std::string _title, uint32_t _width, uint32_t _height);
		window(std::string _title, uint32_t _width, uint32_t _height, bool fullscreen);
		~window();

		
		virtual void handle_event(_event ev);

		GLFWwindow* get_window_ptr();
		uint32_t get_width() const;
		uint32_t get_height() const;
		std::string get_title() const;
	};

}

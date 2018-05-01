#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>

namespace core {
	class shader
	{
		GLint compile(GLint shader_type, const char* shader_source);
		void check_compile_status(GLint shader, GLint shader_type);
		void check_link_status(GLint program);
		
		std::string load_shader(const char* path);

		GLint shader_program;
	public:
		shader();
		shader(const char* vertex_path, const char* fragment_path);
		shader(const char* vertex_path, const char* fragment_path, const char* geometry_path);

		~shader();
		
		void use();
	};

}

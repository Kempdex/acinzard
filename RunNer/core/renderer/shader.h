#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <util/logger.h>

namespace core {
	class shader
	{
		GLint compile(GLint shader_type, const char* shader_source);
		void check_compile_status(GLint shader, GLint shader_type) const;
		void check_link_status(GLint program) const;
		
		std::string load_shader(const char* path);

		GLint id;
	public:
		shader();
		shader(const char* vertex_path, const char* fragment_path);
		shader(const char* vertex_path, const char* fragment_path, const char* geometry_path);

		~shader();
		
		void use() const;

		void set_bool(const char* name, bool value) const;
		void set_int(const char* name, GLint value) const;
		void set_float(const char* name, GLfloat value) const;
		void set_vec2(const char* name, glm::vec2 value) const;
		void set_vec3(const char* name, glm::vec3 value) const;
		void set_mat4(const char* name, glm::mat4 value) const;

	};

}

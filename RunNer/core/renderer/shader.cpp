#include "shader.h"

using namespace core;

shader::shader()
{
	
}

shader::shader(const char * vertex_path, const char * fragment_path)
{
	std::string vertex_shader_source = load_shader(vertex_path);
	std::string fragment_shader_source = load_shader(fragment_path);

	GLint vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_source.c_str());
	GLint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());

	check_compile_status(vertex_shader, GL_VERTEX_SHADER);
	check_compile_status(fragment_shader, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);

	glLinkProgram(id);

	check_link_status(id);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

}

shader::shader(const char* vertex_path, const char* fragment_path, const char* geometry_path)
{
	std::string vertex_shader_source = load_shader(vertex_path);
	std::string fragment_shader_source = load_shader(fragment_path);
	std::string geometry_shader_source = load_shader(geometry_path);


	GLint vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_source.c_str());
	GLint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());
	GLint geometry_shader = compile(GL_GEOMETRY_SHADER, geometry_shader_source.c_str());


	check_compile_status(vertex_shader, GL_VERTEX_SHADER);
	check_compile_status(fragment_shader, GL_FRAGMENT_SHADER);
	check_compile_status(geometry_shader, GL_GEOMETRY_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);
	glAttachShader(id, geometry_shader);

	glLinkProgram(id);

	check_link_status(id);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(geometry_shader);
}


shader::~shader()
{
	//
}

void shader::use() const
{
	glUseProgram(id);
}

void core::shader::set_bool(const char * name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->id, name), (int)value);
}

void shader::set_int(const char* name, GLint value) const
{
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void core::shader::set_float(const char * name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void core::shader::set_vec2(const char * name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}

void core::shader::set_vec3(const char * name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}

void core::shader::set_mat4(const char * name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, &value[0][0]);
}


GLint shader::compile(GLint shader_type, const char* shader_source)
{
	GLint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	return shader;
}

void shader::check_compile_status(GLint shader, GLint shader_type) const
{
	GLint success;
	char info_log[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		if (shader_type == GL_VERTEX_SHADER) {
			printf("ERROR: VERTEX_SHADER_COMPILE :: %s", info_log);//Logger 
		}
		else if (shader_type == GL_FRAGMENT_SHADER) {
			printf("ERROR: FRAGMENT_SHADER_COMPILE :: %s", info_log); //Logger
		}
		else if (shader_type == GL_GEOMETRY_SHADER) {
			printf("ERROR: GEOMETRY_SHADER_COMPILE :: %s", info_log);//Logger
		}
	}
}

void shader::check_link_status(GLint program) const
{
	GLint success;
	char info_log[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, info_log);
		printf("ERROR: PROGRAM_LINKING_FAILED :: %s", info_log);//Logger
	}
}

std::string core::shader::load_shader(const char* path)
{
	std::string shader;

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(path);
		std::stringstream _file_stream;

		_file_stream << file.rdbuf();

		shader = _file_stream.str();
	}
	catch (std::ifstream::failure e) {
		printf("ERROR: Shader file not succesfully read - %s \n", path);
	}

	return shader;
}


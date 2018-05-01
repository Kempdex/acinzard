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

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	glLinkProgram(shader_program);

	check_link_status(shader_program);

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

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glAttachShader(shader_program, geometry_shader);

	glLinkProgram(shader_program);

	check_link_status(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(geometry_shader);
}


shader::~shader()
{
	//
}

void shader::use()
{
	glUseProgram(shader_program);
}


GLint shader::compile(GLint shader_type, const char* shader_source)
{
	GLint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	return shader;
}

void shader::check_compile_status(GLint shader, GLint shader_type)
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

void shader::check_link_status(GLint program)
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


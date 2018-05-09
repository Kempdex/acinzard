#pragma once
#include <map>
#include <glad/glad.h>
#include <engine/engine_module.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <renderer/window.h>

#include <renderer/shader.h>
#include <renderer/texture.h>
#include <renderer/camera.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace core {

	struct character {
		GLuint texture_id;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
	};

	class renderer : public engine_module
	{
		
		GLuint box_VBO;
		GLuint text_VBO;

		glm::mat4 projection;

		camera* _camera;

		window *_window;

		//Используется в большинстве случаев, если только объект не имеет собственный шейдер
		shader* default_shader;
		//Используется в большинстве случаев, если только к тексту не передают собственный шейдер
		shader* default_text_shader;
		//Используется в редких случаях, когда у объекта нет собственной текстуры
		texture* default_texture;
		//

		std::map<GLchar, character> characters;

	public:
		GLuint VAO;
		GLuint text_VAO;
		renderer();
		~renderer();

		void init_renderer(window *win, camera* _cam);

		void load_font(const char *path, uint32_t max_chars);

		void set_default_shader(shader* _shader);

		void set_default_texture(texture* _texture);

		void set_default_text_shader(shader* _shader);

		void clear_screen(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		void draw_object(/*Object here*/);

		/*
			
		*/
		void draw_object(shader* _shader, texture* _texture, glm::mat4 _model);

		/*
			Отрисовывает текст в указанной точке с определенным размером и цветом
			Если не указать шейдер, то используется дефолтный шейдер для текста
		*/
		void draw_text(shader* _shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

		glm::mat4 get_projection() const;

		virtual void handle_event(_event* ev);
	};
}

#include "renderer.h"

using namespace core;

renderer::renderer()
{

}


renderer::~renderer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->box_VBO);
}

void renderer::init_renderer(window *win, camera* cam)
{
	//Setup main renderer
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->box_VBO);

	glBindVertexArray(VAO);

	GLfloat box_vertices[] = {
		 //Position           //Color              //Texture
		 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, box_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertices), box_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Setup text rendering
	glGenVertexArrays(1, &this->text_VAO);
	glBindVertexArray(this->text_VAO);
	glGenBuffers(1, &text_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_window = win;
	_camera = cam;

	projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, (float)_window->get_width(), 0.0f, (float)_window->get_height(), 0.0f, 10.0f);
}

void renderer::load_font(const char * path, uint32_t max_chars)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		logger::error("Could not init FreeType Library");
	}
	FT_Face face;
	if (FT_New_Face(ft, path, 0, &face)) {
		logger::error("Failed to load font");
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < max_chars; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			logger::error("Failed to load glyph -", c);
			continue;
		}

		GLuint char_texture;
		glGenTextures(1, &char_texture);
		glBindTexture(GL_TEXTURE_2D, char_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		character _char = {
			char_texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, character>(c, _char));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void renderer::set_default_shader(shader* _shader)
{
	this->default_shader = _shader;
}

void renderer::set_default_texture(texture* _texture)
{
	this->default_texture = _texture;
}

void renderer::set_default_text_shader(shader * _shader)
{
	this->default_text_shader = _shader;
	//TODO: Изменить установку матрицы для рендера текста
	default_text_shader->use();
	default_text_shader->set_mat4("projection", get_projection());
}

void renderer::clear_screen(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer::draw_object()
{

}

void renderer::draw_object(shader * _shader, texture * _texture, glm::mat4 _model)
{
	shader* _sh = _shader;
	if (!_sh) {
		_sh = default_shader;
	}

	texture* _tx = _texture;
	if (!_tx) {
		_tx = default_texture;
	}

	glActiveTexture(GL_TEXTURE0);
	_sh->use();
	_tx->bind();
	glm::mat4 MVP = projection * _camera->get_view_matrix() * _model;
	_sh->set_mat4("MVP", MVP);

	glBindVertexArray(VAO);

	//TODO: Придумать куда и как запихнуть эти магические 0 и 8
	glDrawArrays(GL_TRIANGLES, 0, 8);

	glBindVertexArray(0);
}

void renderer::draw_text(shader * _shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader* _sh = _shader;
	if (!_sh) {
		_sh = default_text_shader;
	}

	_sh->use();
	_sh->set_vec3("text_color", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text_VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h, 0.0, 0.0 },
			{ xpos,     ypos,     0.0, 1.0 },
			{ xpos + w, ypos,     1.0, 1.0 },

			{ xpos,     ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos,     1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.texture_id);

		glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		x += (ch.advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

glm::mat4 renderer::get_projection() const
{
	return this->projection;
}

void renderer::handle_event(_event* ev)
{
	//No imp
}

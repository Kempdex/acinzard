#include "texture.h"

using namespace core;

//Ctor with default texture settings
texture::texture(const char * path)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char *image = stbi_load(path, &width, &height, &nr_channels, 0);
	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		core::logger::error("Failed to load texture from path", path);
	}
	stbi_image_free(image);
}

//Ctor with more texture settings
texture::texture(const char * path, GLint _texture_wrap_s, GLint _texture_wrap_t, GLint _texture_min_filter, GLint _texture_mag_filter)
	:texture_wrap_s(_texture_wrap_s), texture_wrap_t(_texture_wrap_t), texture_min_filter(_texture_min_filter), texture_mag_filter(_texture_mag_filter)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_mag_filter);

	stbi_set_flip_vertically_on_load(true);
	unsigned char *image = stbi_load(path, &width, &height, &nr_channels, 0);
	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		core::logger::error("Failed to load texture from path", path);
	}
	stbi_image_free(image);
}


texture::~texture()
{
	//
}

void texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

GLint core::texture::get_width()
{
	return this->width;
}

GLint core::texture::get_height()
{
	return this->height;
}

GLint core::texture::get_nr_channels()
{
	return this->nr_channels;
}


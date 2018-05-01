#pragma once
#include <glad/glad.h>
#include <util/stb_image.h>

namespace core {
	class texture
	{
		GLuint id;

		GLint width;
		GLint height;
		GLint nr_channels;

		GLint texture_wrap_s;
		GLint texture_wrap_t;

		GLint texture_min_filter;
		GLint texture_mag_filter;
	public:
		texture(const char* path);
		texture(const char* path, GLint _texture_wrap_s, GLint _texture_wrap_t, GLint _texture_min_filter, GLint _texture_mag_filter);
		~texture();

		void bind();
		GLint get_width();
		GLint get_height();
		GLint get_nr_channels();
	};
}

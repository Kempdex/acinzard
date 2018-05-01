#version 330 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec3 _color;
layout (location = 2) in vec2 _texture_coords;

out vec3 color;
out vec2 texture_coords;

uniform mat4 MVP;

void main() {
	color = _color;
	texture_coords = _texture_coords;
	gl_Position = MVP * vec4(_pos, 1.0);
}

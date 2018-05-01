#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 _color;

out vec3 color;

void main() {
	color = _color;
	gl_Position = vec4(pos, 1.0);
}

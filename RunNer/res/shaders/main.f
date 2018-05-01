#version 330 core
out vec4 frag_color;

in vec2 texture_coords;
in vec3 color;

uniform sampler2D _texture;

void main() {
	frag_color = texture(_texture, texture_coords) * vec4(color, 1.0);
}
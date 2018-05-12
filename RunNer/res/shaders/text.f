#version 330 core
in vec2 tex_coords;
out vec4 color;

uniform sampler2D text;
uniform vec3 text_color;

const float width = 0.4;
const float edge = 0.2;

const float border_width = 0.7;
const float border_edge = 0.1;

const vec3 outline_color = vec3(1.0, 1.0, 1.0);

void main() {
	
	float distance = 1.0 - texture(text, tex_coords).r;
	float alpha = 1.0 - smoothstep(width, width + edge, distance);

	//Using for glow text
	float distance2 = 1.0 - texture(text, tex_coords).r;
	float outline_alpha = 1.0 - smoothstep(border_width, border_width + border_edge, distance2);

	float overall_alpha = alpha + (1.0 - alpha) * outline_alpha;

	vec3 overall_color = mix(outline_color, text_color, alpha/overall_alpha);

	color = vec4(text_color, alpha);
}
#version 330 core


in vec2 sample_position;

out vec4 output_color;

uniform sampler2D tex;


void main()
{
	output_color = texture(tex, sample_position);
}

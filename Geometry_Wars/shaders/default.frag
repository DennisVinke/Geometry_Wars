#version 330 core

in vec4 vertex_color;

out vec4 color_out;


void main()
{
	color_out = vertex_color;
}

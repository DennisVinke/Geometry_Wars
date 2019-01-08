#version 330 core

//in vec4 vertex_color;

out vec4 color_out;

uniform vec4 color;


void main()
{
	color_out = color;
	//color_out = vertex_color;
}

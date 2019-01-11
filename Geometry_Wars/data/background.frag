#version 330 core

in float col;

out vec4 output_color;


void main()
{
	output_color = vec4(col, col, col, 1);
}

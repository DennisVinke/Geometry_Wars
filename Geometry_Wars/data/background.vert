#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in float color;

out float col;

void main()
{
	gl_Position = vec4(position, 1, 1);
	col = color;
}

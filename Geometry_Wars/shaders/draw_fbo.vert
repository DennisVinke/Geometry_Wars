#version 330 core

layout(location = 0) in vec2 position;

out vec2 tex_coord;


void main()
{
	gl_Position.xy = position;
	tex_coord.x = 0.5 * (position.x + 1);
	tex_coord.y = 0.5 * (position.y + 1);
}

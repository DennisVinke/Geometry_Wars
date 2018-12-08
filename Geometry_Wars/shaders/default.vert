#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

uniform vec2 viewport;
uniform mat3 transformation;



out vec4 vertex_color;




float map(float value, float from_min, float from_max, float to_min, float to_max) 
{
	return to_min + (to_max - to_min) * (value - from_min) / (from_max - from_min);
}


void main()
{
	vec3 pos = transformation * vec3(position, 1.0f);

	gl_Position.x = map(pos.x, 0, viewport.x, -1,  1);
	gl_Position.y = map(pos.y, 0, viewport.y,  1, -1);
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	vertex_color = color;
}
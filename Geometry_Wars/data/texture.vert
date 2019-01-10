#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 tex_coord;

out vec2 sample_position;

uniform vec2 viewport;



float map(float value, float from_min, float from_max, float to_min, float to_max) 
{
	return to_min + (to_max - to_min) * (value - from_min) / (from_max - from_min);
}


void main()
{
	sample_position = tex_coord;
	
	gl_Position.x = map(position.x, 0, viewport.x, -1,  1);
	gl_Position.y = map(position.y, 0, viewport.y,  1, -1);
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
}

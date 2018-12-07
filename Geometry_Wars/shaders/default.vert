#version 330 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec4 vertex_color;

out vec4 color;


uniform int use_uniform_color;
uniform vec4 uniform_color;


void main()
{
  gl_Position.xy = vertex_position;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  if (use_uniform_color == 1)
  {
  	color = uniform_color;
  }
  else
  {
  	color = vertex_color;
  }
}
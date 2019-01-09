#version 330 core

//in vec4 vertex_color;

out vec4 color_out;



uniform vec4 color;




//LOOOL
vec3 hsv2rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main()
{
	color_out.xyz = hsv2rgb(color.xyz);
	color_out.w = 1;

	//color_out = vertex_color;
}

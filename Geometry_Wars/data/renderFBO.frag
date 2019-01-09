#version 330 core


out vec4 output_color;


uniform sampler2D tex;

uniform ivec2 viewport;


void main()
{
	vec2 pos = gl_FragCoord.xy / viewport;

	output_color = texture(tex, pos);
}

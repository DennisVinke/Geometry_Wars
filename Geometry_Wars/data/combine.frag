#version 330 core

out vec4 output_color;

uniform ivec2 viewport;
uniform vec2 weights;

uniform sampler2D tex1;
uniform sampler2D tex2;


void main()
{
	vec2 pos = gl_FragCoord.xy / viewport;

	vec4 color1 = texture(tex1, pos);
	vec4 color2 = texture(tex2, pos);

	output_color = weights.x * color1 + weights.y * color2;
}

#version 330 core

out vec4 output_color;


uniform sampler2D tex;

uniform int blur_amount;

uniform int window_width;
uniform int window_height;


void main()
{
	float pw = 1.0f / window_width;
	float ph = 1.0f / window_height;

	vec2 base = gl_FragCoord.xy / vec2(window_width, window_height);

	vec4 s0 = texture(tex, vec2(base.x - 3 * pw, base.y)) * 0.00598;
	vec4 s1 = texture(tex, vec2(base.x - 2 * pw, base.y)) * 0.060626;
	vec4 s2 = texture(tex, vec2(base.x - 1 * pw, base.y)) * 0.241843;
	vec4 s3 = texture(tex, vec2(base.x + 0 * pw, base.y)) * 0.383103;
	vec4 s4 = texture(tex, vec2(base.x + 1 * pw, base.y)) * 0.241843;
	vec4 s5 = texture(tex, vec2(base.x + 2 * pw, base.y)) * 0.060626;
	vec4 s6 = texture(tex, vec2(base.x + 3 * pw, base.y)) * 0.00598;

	output_color = 1.2 * (s0 + s1 + s2 + s3 + s4 + s5 + s6);
}
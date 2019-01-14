#version 330 core

out vec4 output_color;

uniform ivec2 viewport;
uniform vec2 weights;

uniform sampler2D tex1;
uniform sampler2D tex2;

uniform mat3 r_transform;
uniform mat3 g_transform;
uniform mat3 b_transform;

uniform int inverted;


void main()
{
	vec3 pos = vec3(gl_FragCoord.xy , 1);

	vec3 r_pos = r_transform * pos;
	vec3 g_pos = g_transform * pos;
	vec3 b_pos = b_transform * pos;

	float r = weights.x * texture(tex1, r_pos.xy / viewport).r + weights.y * texture(tex2, r_pos.xy / viewport).r;
	float g = weights.x * texture(tex1, g_pos.xy / viewport).g + weights.y * texture(tex2, g_pos.xy / viewport).g;
	float b = weights.x * texture(tex1, b_pos.xy / viewport).b + weights.y * texture(tex2, b_pos.xy / viewport).b;

	if (inverted != 0)
	{
		output_color = vec4(1-r, 1-g, 1-b, 1);
	}
	else
	{
		output_color = vec4(r, g, b, 1);
	}
}

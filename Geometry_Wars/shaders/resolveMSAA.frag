#version 330 core

out vec4 output_color;


uniform sampler2DMS tex;
uniform int amount;


void main()
{
	vec4 total_color = vec4(0, 0, 0, 0);

	for (int i = 0; i < amount; ++i)
	{
		total_color += texelFetch(tex, ivec2(gl_FragCoord.xy), i);
	}

	output_color = total_color / amount;
}

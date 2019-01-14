#version 330 core

out vec4 output_color;


uniform sampler2D tex;

uniform int blur_amount;

uniform int window_width;
uniform int window_height;


void main()
{
	float pixel_width = 1.0f / window_width;
	float pixel_height = 1.0f / window_height;

	vec2 base = gl_FragCoord.xy / vec2(window_width, window_height);
	/*
	vec4 s0 = texture(tex, vec2(base.x, base.y - 3 * pixel_height));// * 0.00598;
	vec4 s1 = texture(tex, vec2(base.x, base.y - 2 * pixel_height));// * 0.060626;
	vec4 s2 = texture(tex, vec2(base.x, base.y - 1 * pixel_height));// * 0.241843;
	vec4 s3 = texture(tex, vec2(base.x, base.y + 0 * pixel_height));// * 0.383103;
	vec4 s4 = texture(tex, vec2(base.x, base.y + 1 * pixel_height));// * 0.241843;
	vec4 s5 = texture(tex, vec2(base.x, base.y + 2 * pixel_height));// * 0.060626;
	vec4 s6 = texture(tex, vec2(base.x, base.y + 3 * pixel_height));// * 0.00598;
	*/
	//vec3 original_color0 = s0.a == 0 ? vec3(0, 0, 0) : vec3(s0.rgb / s0.a);
	float weight[7] = float[7](0.00598, 0.060626, 0.241843, 0.383103, 0.241843, 0.060626, 0.00598);
	vec4 sample_color[7];
	vec3 original_color[7];

	float total_weight;
	vec3 total_color;
	float alpha;
	int col_count = 0;

	for (int i = 0; i < 7; ++i)
	{
		sample_color[i] = texture(tex, vec2(base.x, base.y + (i-3) * pixel_height));
		alpha += sample_color[i].a * weight[i];

		if (sample_color[i].a == 0)
		{
			original_color[i] = vec3(0, 0, 0);
		}
		else
		{
			original_color[i] = sample_color[i].rgb / sample_color[i].a;
			total_weight += weight[i];
			total_color += original_color[i] * weight[i];
			col_count ++;
 		}
		//original_color[i] = sample_color[i].a == 0 ? vec3(0, 0, 0) : vec3(sample_color[i].rgb / sample_color[i].a);
	}

	output_color.rgb = total_color / total_weight;
	output_color.a = 1;
}

/*
    vec4 original_color0 = vec4(s0.rgb / s0.a, s0.a) * 0.00598; //texture(tex, vec2(base.x - 3 * pixel_width, base.y));// * 0.00598;
	vec4 original_color1 = vec4(s1.rgb / s1.a, s1.a) * 0.060626; //texture(tex, vec2(base.x - 2 * pixel_width, base.y));// * 0.060626;
	vec4 original_color2 = vec4(s2.rgb / s2.a, s2.a) * 0.241843; //texture(tex, vec2(base.x - 1 * pixel_width, base.y));// * 0.241843;
	vec4 original_color3 = vec4(s3.rgb / s3.a, s3.a) * 0.383103; //texture(tex, vec2(base.x + 0 * pixel_width, base.y));// * 0.383103;
	vec4 original_color4 = vec4(s4.rgb / s4.a, s4.a) * 0.241843; //texture(tex, vec2(base.x + 1 * pixel_width, base.y));// * 0.241843;
	vec4 original_color5 = vec4(s5.rgb / s5.a, s5.a) * 0.060626; //texture(tex, vec2(base.x + 2 * pixel_width, base.y));// * 0.060626;
	vec4 original_color6 = vec4(s6.rgb / s6.a, s6.a) * 0.00598; //texture(tex, vec2(base.x + 3 * pixel_width, base.y));// * 0.00598;

	output_color = (original_color0 + original_color1 + original_color2 + original_color3 + original_color4 + original_color5 + original_color6);
}*/

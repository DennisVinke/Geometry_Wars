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
	

	//output_color /= weights.x + weights.y;
	
	//vec3 hdr = weights.x * color1.xyz + weights.y * color2.xyz;
	//vec3 mapped = hdr / (hdr + 1.0f);
	//output_color.xyz = pow(mapped, vec3(1.0 / 2.2));
	//output_color.w = 1;

	//vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
  
    // reinhard tone mapping
    //vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
    // gamma correction 
    //mapped = pow(mapped, vec3(1.0 / gamma));
  

	//if (color1.r + color1.g + color1.b > color2.r + color2.g + color2.b)
	//if (gl_FragCoord.x > 200)
	//{
	//	output_color = color1;
	//}
	//else 
	//{
	//	output_color = color2;
	//}

//	vec4 total_color = vec4(0, 0, 0, 0);

//	for (int i = 0; i < amount; ++i)
//	{
//		total_color += texelFetch(tex, ivec2(gl_FragCoord.xy), i);
//	}

//	output_color = total_color / amount;
}

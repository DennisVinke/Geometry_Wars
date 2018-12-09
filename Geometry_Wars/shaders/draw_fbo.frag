#version 330 core

in vec2 tex_coord;

out vec4 color_out;

uniform sampler2DMS tex;


vec4 ReadMultisampledTexture(in sampler2DMS tex, in ivec2 pos, in int numSamples)
{
  vec4 texel = vec4(0,0,0,0);
  for (int i = 0; i < numSamples; ++i)
  {
	vec4 sample = texelFetch(tex, pos, i);
	
	texel += sample;
  }
  
  return texel / float(numSamples);
}

vec4 ReadMultisampledTexture(in sampler2DMS tex, in vec2 texcoord, in int numSamples)
{
  ivec2 pos = ivec2(texcoord * vec2(textureSize(tex)));
  return ReadMultisampledTexture(tex, pos, numSamples);
}


void main()
{
	color_out = ReadMultisampledTexture(tex, tex_coord, 8).yxzw;
}

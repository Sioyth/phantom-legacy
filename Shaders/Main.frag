#version 460

in vec2 textureOut;
in vec3 colorOut;

out vec4 pixelColor;

uniform sampler2D textureImage;
uniform int isTextured;

void main()
{

	vec2 v;
	v.s = 0.5f;
	v.t = 0.5f;
	if(isTextured == 1)
	{
		pixelColor = vec4(colorOut, 1.0) * texture(textureImage, v); 
   }
   else
   {
		pixelColor = vec4(colorOut, 1.0);
   }
} 
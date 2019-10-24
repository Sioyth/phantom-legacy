#version 460

in vec2 textureOut;
in vec3 colorOut;

out vec4 pixelColor;

uniform sampler2D textureImage;
uniform int isTextured;

// uniform sampler2D textureImage2;

void main()
{
	if(isTextured == 1)
	{
		pixelColor = vec4(colorOut, 1.0) * texture(textureImage, textureOut); // mix(texture(textureImage, textureOut), texture(textureImage, textureOut), 0.5);
   }
   else
   {
		pixelColor = vec4(colorOut, 1.0);
   }
} 
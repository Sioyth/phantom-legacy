#version 460

in vec2 textureOut;
in vec3 colorOut;

out vec4 pixelColor;

uniform int isLit;
uniform int isTextured;
uniform vec3 lightColor;
uniform sampler2D textureImage;

// uniform sampler2D textureImage2;

void main()
{
	if(isLit == 0)
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
   else
   {
	   if(isTextured == 1)
	   {
			pixelColor =  vec4(colorOut, 1.0) * texture(textureImage, textureOut) * vec4(lightColor, 1.0);
	   }
	   else
	   {
			pixelColor = vec4(colorOut, 1.0); //* vec4(lightColor, 1.0);
	   }
   }
} 
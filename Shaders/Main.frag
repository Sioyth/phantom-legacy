#version 460

uniform float time;
in vec3 colorOut;
out vec4 pixelColor;

void main()
{
   pixelColor = vec4(colorOut, 1.0); // * ((sin(time) + 1) / 2);
} 
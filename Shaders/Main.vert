#version 460

in vec3 colorIn;
in vec3 vertexIn;
in vec2 textureIn;

out vec3 vertexOut;
out vec3 colorOut;
out vec2 textureOut;

// TODO do it outside the shader in the application
uniform int isLit;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 cameraPosition;

void main()
{

	vertexOut = (model * vec4(vertexIn, 1.0)).xyz;

	colorOut = colorIn;

	// Send interpolated UV coordinates value to the fragment shader;
	textureOut = textureIn;

    gl_Position = proj * view * model * vec4(vertexIn, 1.0);
}
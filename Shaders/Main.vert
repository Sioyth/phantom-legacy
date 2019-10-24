#version 460

in vec3 vertexIn;
in vec3 colorIn;
in vec2 textureIn;

out vec3 colorOut;
out vec2 textureOut;

// Todo do it outside the shader in the application
uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 proj;

void main()
{
	// Send interpolated color value to the fragment shader;
	colorOut = colorIn;

	// Send interpolated UV coordinates value to the fragment shader;
	textureOut = textureIn;

    gl_Position = proj * view * model * vec4(vertexIn, 1.0);
}
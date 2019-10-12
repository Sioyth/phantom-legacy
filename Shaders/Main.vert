#version 460

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

// Todo do it outside the shader in the application
uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 proj;

void main()
{
	colorOut = colorIn;
    gl_Position = proj * view * model * vec4(vertexIn, 1.0);
}
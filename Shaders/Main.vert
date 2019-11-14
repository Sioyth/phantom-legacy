#version 460

//struct Light
//{
//vec3 position;
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
//};
//
//struct Material
//{
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
//float metallic;
//};

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

//uniform Light light;
//uniform Material material;
//
uniform vec3 cameraPosition;

void main()
{
//	if(isLit == 1)
//	{
//		vec3 normal = vec3(0.0f, 1.0f, 0.0f);
//		// -------------------------------------------# Create ambient lightning
//
//		vec3 ambientColor = light.ambient * material.ambient;
//
//		// -------------------------------------------# calculate the diffuse color
//
//		//determine the vertex in world space for calculations below
//		vec3 vertexPosition = (model * vec4(vertexIn, 1.0)).xyz;
//
//		//calculate the light direction based on light’s position and vertex position
//		vec3 lightDirection = normalize(light.position - vertexPosition);
//
//		//calculate the light intensity value
//		float lightIntensity = max(dot(lightDirection, normal), 0.0);
//
//		//calculate the diffuse color
//		vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;
//
//		// -------------------------------------------# calculate the specular color
//		
//		//calculate the view direction based on camera’s position and vertex position
//		vec3 viewDirection = normalize(cameraPosition - vertexPosition);
//
//		//calculate the reflection based on reversed light direction and normal vectors
//		vec3 reflection = reflect(-lightDirection, normal);
//
//		//calculate the specular term using the reflection and view direction vectors
//		float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.metallic);
//
//		//calculate the specular color
//		vec3 specularColor = light.specular * material.specular * specularTerm;
//
//		colorOut =  ambientColor + diffuseColor + specularColor;
//
//	}
//	else
//	{
//		// Send interpolated color value to the fragment shader;
//		colorOut = colorIn;
//	}

	vertexOut = vertexIn;

	colorOut = colorIn;

	// Send interpolated UV coordinates value to the fragment shader;
	textureOut = textureIn;

    gl_Position = proj * view * model * vec4(vertexIn, 1.0);
}
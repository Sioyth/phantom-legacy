#version 460

#define TOTAL_LIGHTS 4

// -------------------------------------------# Structs

struct Light
{
vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;

float attenuationConst;
float attenuationLinear;
float attenuationQuad;

};

struct Material
{
vec3 ambient;
vec3 diffuse;
vec3 specular;
float metallic;
};

// -------------------------------------------# In

in vec2 textureOut;
in vec3 colorOut;
in vec3 vertexOut;
//in vec3 normalOut;

// -------------------------------------------# Out

out vec4 pixelColor;

// -------------------------------------------# Uniforms

uniform int isLit;
uniform int isTextured;
uniform vec3 lightColor;
uniform sampler2D textureImage;

uniform Light light;
uniform Light lights[TOTAL_LIGHTS];
uniform Material material;

uniform mat4 model;
uniform vec3 cameraPosition;

// uniform sampler2D textureImage2;

// -------------------------------------------# Variables

vec3 lightDirection;

// -------------------------------------------# Functions

vec3 CalculateAmbient();
vec3 CalculateDiffuse();
vec3 CalculeSpecular();
float CalculateAttenuation();


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
		 // -------------------------------------------# normalize normal

		//vec3 normal = normalize(normalOut);

		 // -------------------------------------------# Create ambient lightning

		vec3 ambientColor = CalculateAmbient();

		// -------------------------------------------# calculate the diffuse color

		vec3 diffuseColor = CalculateDiffuse();

		// -------------------------------------------# calculate the specular color

		vec3 specularColor = CalculeSpecular();

		// -------------------------------------------# Attenuation Formula

		float attenuation = CalculateAttenuation();

	   if(isTextured == 1)
	   {
			pixelColor =  vec4(colorOut, 1.0) * texture(textureImage, textureOut) * vec4((ambientColor + diffuseColor + specularColor) * attenuation, 1.0);// * vec4(lightColor, 1.0);
	   }
	   else
	   {
			pixelColor =  vec4((ambientColor + diffuseColor + specularColor) * attenuation, 1.0);
	   }
   }
} 

vec3 CalculateAmbient()
{
	// -------------------------------------------# Calculate Ambient Light
	return  light.ambient * material.ambient;
}

vec3 CalculateDiffuse()
{
	// -------------------------------------------# calculate the diffuse color

	vec3 normal = vec3(0.0f, 1.0f, 0.0f);

	//calculate the light direction based on light�s position and vertex position
	lightDirection = normalize(light.position - vertexOut);

	//calculate the light intensity value
	float lightIntensity = max(dot(lightDirection, normal), 0.0);
		
	//calculate the diffuse color
	return light.diffuse * material.diffuse * lightIntensity;
}

vec3 CalculeSpecular()
{
	// -------------------------------------------# calculate the specular color
		
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);

	//calculate the view direction based on camera�s position and vertex position
	vec3 viewDirection = normalize(cameraPosition - vertexOut);

	//calculate the reflection based on reversed light direction and normal vectors
	vec3 reflection = reflect(-lightDirection, normal);

	//calculate the specular term using the reflection and view direction vectors
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.metallic);

	//calculate the specular color
	return light.specular * material.specular * specularTerm;
}

float CalculateAttenuation()
{
	// -------------------------------------------# calculate attenuation
	float distanceFromLight = length(light.position - vertexOut);
	return 1 / (light.attenuationConst + light.attenuationLinear * distanceFromLight + light.attenuationQuad * pow(distanceFromLight, 2.0));
}
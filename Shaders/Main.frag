#version 460

#define TOTAL_LIGHTS 5

#define POINT_LIGHT 1
#define DIRECTIONAL_LIGHT 2


// -------------------------------------------# Structs

struct Light
{

int type;
//int isActive;

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
uniform int lightsActiveNumber;
uniform vec3 lightColor;
uniform sampler2D textureImage;

uniform Light lights[TOTAL_LIGHTS];
uniform Material material;

uniform mat4 model;
uniform vec3 cameraPosition;

// uniform sampler2D textureImage2;

// -------------------------------------------# Variables

float attenuation;
vec3 lightDirection;

// -------------------------------------------# Functions

vec3 CalculateAmbient(Light light);
vec3 CalculateDiffuse(Light light);
vec3 CalculeSpecular(Light light);
float CalculateAttenuation(Light light);


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

		for(int i = 0; i < lightsActiveNumber; i++)
		{

		
			//  Create ambient lightning
			vec3 ambientColor = CalculateAmbient(lights[i]);

			// calculate the diffuse color
			vec3 diffuseColor = CalculateDiffuse(lights[i]);

			// calculate the specular color
			vec3 specularColor = CalculeSpecular(lights[i]);

			if(lights[i].type == POINT_LIGHT)
			{
			
				// Calculate Attenuation
				attenuation = CalculateAttenuation(lights[i]);

				// Apply
			   if(isTextured == 1)
			   {
					pixelColor +=  vec4(colorOut, 1.0) * texture(textureImage, textureOut) * vec4((ambientColor + diffuseColor + specularColor) * attenuation, 1.0);// * vec4(lightColor, 1.0);
			   }
			   else
			   {
					pixelColor +=  vec4((ambientColor + diffuseColor + specularColor) * attenuation, 1.0);
			   }

			}
			else if(lights[i].type == DIRECTIONAL_LIGHT)
			{

				// Apply
			   if(isTextured == 1)
			   {
					pixelColor +=  vec4(colorOut, 1.0) * texture(textureImage, textureOut) * vec4((ambientColor + diffuseColor + specularColor), 1.0);// * vec4(lightColor, 1.0);
			   }
			   else
			   {
					pixelColor +=  vec4((ambientColor + diffuseColor + specularColor), 1.0);
			   }
			}
	   }
   }
} 

vec3 CalculateAmbient(Light light)
{
	// -------------------------------------------# Calculate Ambient Light
	return  light.ambient * material.ambient;
}

vec3 CalculateDiffuse(Light light)
{
	// -------------------------------------------# calculate the diffuse color

	vec3 normal = vec3(0.0f, 1.0f, 0.0f);

	//calculate the light direction based on light�s position and vertex position
	
	if(light.type == POINT_LIGHT)
	{
		lightDirection = normalize(light.position - vertexOut);
	}
	else if(light.type == DIRECTIONAL_LIGHT)
	{
		lightDirection = normalize(light.position);
	}

	//calculate the light intensity value
	float lightIntensity = max(dot(lightDirection, normal), 0.0);
		
	//calculate the diffuse color
	return light.diffuse * material.diffuse * lightIntensity;
}

vec3 CalculeSpecular(Light light)
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

float CalculateAttenuation(Light light)
{
	// -------------------------------------------# calculate attenuation
	float distanceFromLight = length(light.position - vertexOut);
	return 1 / (light.attenuationConst + light.attenuationLinear * distanceFromLight + light.attenuationQuad * pow(distanceFromLight, 2.0));
}
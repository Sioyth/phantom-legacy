#include <SDL_image.h>
#include "Texture.h"
#include "Debug.h"

std::map<std::string, Texture>* Texture::s_textureMap = new std::map<std::string, Texture>;

Texture::Texture()
{
	m_ID = 0;
}

GLuint Texture::GetTexture(const std::string& textureID)
{
	return GLuint();
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

bool Texture::LoadTexture()
{
	// -------------------------------------------#  load the raw image file into RAM

	// load the raw image data from file and store in Ram
	SDL_Surface* textureData = nullptr;
	textureData = IMG_Load("Textures/Water_2.jpg");

	// if image date could not be load, return false;
	if (!textureData)
	{
		Debug::ErrorLog("Error loading texture file!");
		return false;
	}

	// extract raw image data and store in variables for use below (easier)
	GLsizei width = textureData->w;
	GLsizei height = textureData->h;
	Uint8* pixels = (Uint8*)textureData->pixels;
	Uint8 depth = textureData->format->BytesPerPixel;
	GLint format = (depth == 4) ? GL_RGBA : GL_RGB;

	// -------------------------------------------#  create the texture object in VRAM

	// create texture id for our texture object (VRAM)
	glGenTextures(1, &m_ID);

	// bind the texture ID
	glBindTexture(GL_TEXTURE_2D, m_ID);
	{
		// Set default filtering
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//create the texture object in VRAM extracted above
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	}

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	// release ram Image;
	SDL_FreeSurface(textureData);

	// add new texture image to the map
	(*s_textureMap)["Crate"] = *this;
	//s_textureMap->insert(std::pair<std::string, Texture>("CRATE", *this));

	return true;
}

void Texture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UnloadTexture()
{
	glDeleteTextures(1, &m_ID);
}

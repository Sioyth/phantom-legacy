#pragma once

#include <map>
#include <string>
#include "glad/glad.h"

class Texture
{
public:

	Texture();

public:

	static GLuint GetTexture(const std::string& textureID);

public:

	void BindTexture();
	bool LoadTexture(const std::string& filename, const std::string& textureName);
	void UnbindTexture();
	void UnloadTexture();

private:

	static std::map<std::string, Texture>* s_textureMap;

private:

	GLuint m_ID;
};


#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#include <iostream>
#include <string>

class Texture
{
private:
	unsigned int m_textureID;

public:
	Texture(const char* texturePath, bool isPng, bool reverse);
	void use(GLenum texture);

	unsigned int getID()
	{
		return m_textureID;
	}
};

#endif

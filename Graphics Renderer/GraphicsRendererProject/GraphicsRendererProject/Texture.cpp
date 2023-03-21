#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string filename)
{
}

Texture::~Texture()
{
	if (loadedProperly) glDeleteTextures(1, &textureID);
}

void Texture::LoadFromFile(std::string filename)
{
}

void Texture::Bind(int textureUnit) const
{
}

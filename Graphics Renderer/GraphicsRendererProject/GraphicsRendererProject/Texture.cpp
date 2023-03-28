#include "Image.h"
#include "Texture.h"
#include <iostream>

Texture::Texture(std::string filename)
{
	//Reads the file in Working folder with the same name as string provided
	LoadFromFile(filename);
	if (loadedProperly)
		std::cout << "Texture " << filename << " has loaded properly" << std::endl;
}

Texture::~Texture()
{
	//Checks to see if the texture was correctly loaded and if so will delete the textureID
	if (loadedProperly) glDeleteTextures(1, &textureID);
}

void Texture::LoadFromFile(std::string filename)
{
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channelCount, 0);

	//Generates and binds the texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Load for RGB
	if (channelCount == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	//Load for RGBA
	else if (channelCount == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}

	//Creates parameter ints for the minimum and the magnitude
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Unbinds Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//Frees the image
	stbi_image_free(imageData);
	loadedProperly = true;
}

void Texture::Bind(int textureUnit) const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

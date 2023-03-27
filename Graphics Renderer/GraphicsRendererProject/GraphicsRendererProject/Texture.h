#pragma once

#include "Graphics.h"
#include <string>

class Texture
{
	unsigned int textureID;
	int width, height, channelCount;
	bool loadedProperly;

public:
	Texture();
	Texture(std::string filename);
	~Texture();

	//Loads texture from file
	void LoadFromFile(std::string filename);

	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;

	//Binds texture
	void Bind(int textureUint = 0) const;

	//Unbinds texture
	static void Unbind(int textureUnit = 0);
};
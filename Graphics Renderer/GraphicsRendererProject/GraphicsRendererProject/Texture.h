#pragma once

#include "Graphics.h"
#include <string>

class Texture
{
	unsigned int textureID;
	bool loadedProperly;
	int width, height, channelCount;

public:
	Texture();
	Texture(std::string filename);
	~Texture();

	void LoadFromFile(std::string filename);

	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;

	void Bind(int textureUnit = 0) const;
};
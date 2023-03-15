#pragma once

#include "glm.hpp"
#include <string>
#include "Graphics.h"

class ShaderProgram
{
private:
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	GLuint shaderProgramID;

	bool loadedProperly = false;

public:
	ShaderProgram();

	void LoadFromFiles(std::string vertexShaderName, std::string fragmentShaderName);

	void Enable();

	~ShaderProgram();

	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;

	void SetFloatUniform(std::string variableName, float value);
};

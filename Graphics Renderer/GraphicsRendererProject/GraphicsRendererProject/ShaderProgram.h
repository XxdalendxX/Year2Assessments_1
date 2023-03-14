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

public:
	ShaderProgram();

	void LoadFromFiles(std::string vertexShaderName, std::string fragmentShaderName);

	~ShaderProgram();

	//ShaderProgram(const &ShaderProgram()) = delete;
};

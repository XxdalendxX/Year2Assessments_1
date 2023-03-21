#pragma once

#include "glm.hpp"
#include <string>
#include "Graphics.h"

class ShaderProgram
{
private:
	GLuint vertexShaderID; //vertex shader generation
	GLuint fragmentShaderID; //fragment shader generation

	GLuint shaderProgramID; //shader program generation

	bool loadedProperly = false; //checks to see if everything has loaded properly

public:
	ShaderProgram();

	//Load shader code from the vertex shader file and the fragment shader file
	void LoadFromFiles(std::string vertexShaderName, std::string fragmentShaderName);

	//Enables the shader program
	void Enable();

	//destroys the shader program
	~ShaderProgram();

	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;

	//sets the float uniform of a variable in a shader file
	void SetFloatUniform(std::string variableName, float value);
	//sets the Matrix uniform of a variable in a shader file
	void SetMatrixUniform(std::string variableName, glm::mat4 value);
};

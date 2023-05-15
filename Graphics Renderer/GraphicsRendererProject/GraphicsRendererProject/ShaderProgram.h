#pragma once

#include "glm.hpp"
#include "Text.h"
#include "Graphics.h"
#include "Maths.h"

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

	//sets the Float uniform of a variable in a shader file
	void SetFloatUniform(std::string variableName, float value);
	//sets the Matrix uniform of a variable in a shader file
	void SetMatrixUniform(std::string variableName, mat4 value);
	//sets the Vector uniform of a variable in a shader file
	void SetVectorUniform(std::string variableName, vec3 value);

	void SetVectorUniform(std::string variableName, int count, vec3* value);
	//sets the Integer uniform of a variable in a shader file
	void SetIntergerUniform(std::string variableName, int value);
};

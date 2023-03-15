#include "ShaderProgram.h"
#include "Utilities.h"
#include <iostream>

void ShaderProgram::LoadFromFiles(std::string vertexShaderName, std::string fragmentShaderName)
{
	loadedProperly = true;

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	shaderProgramID = glCreateProgram();

	std::string vertexSource = LoadFileAsString(vertexShaderName);
	std::string fragmentSource = LoadFileAsString(fragmentShaderName);

	const char* vertexSourceC = vertexSource.c_str();

	glShaderSource(vertexShaderID, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShaderID);

	GLchar errorLog[555];
	GLint successStatus = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &successStatus);
	if (successStatus == GL_FALSE)
	{
		std::cout << "Oh nooo~... Vertex shader compilation failed for whatever reason." << std::endl;
		glGetShaderInfoLog(vertexShaderID, 555, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedProperly = false;
	}
	else
	{
		std::cout << "Yeah, vertex shader's doing a-okay." << std::endl;
	}

	const char* fragmentSourceC = fragmentSource.c_str();

	glShaderSource(fragmentShaderID, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &successStatus);
	if (successStatus == GL_FALSE)
	{
		std::cout << "Oopsie... Fragment shader compilation has crashed and burned for some reason." << std::endl;
		glGetShaderInfoLog(fragmentShaderID, 555, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedProperly = false;
	}
	else
	{
		std::cout << "Good news, fragment shader has not crashed and burned... Yet." << std::endl;
	}

	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &successStatus);

	if (successStatus == GL_FALSE)
	{
		std::cout << "Ah well... Shader link has been unsuccessfully completed for one reason or another." << std::endl;
		glGetShaderInfoLog(shaderProgramID, 555, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedProperly = false;
	}

	if (loadedProperly)
	{
		std::cout << "So here's the thing... The shader has indeed loaded properly." << std::endl;
	}
}

void ShaderProgram::Enable()
{
	glUseProgram(shaderProgramID);
}

ShaderProgram::~ShaderProgram()
{
	//clean up shader program stuff here
}

void ShaderProgram::SetFloatUniform(std::string variableName, float value)
{
	GLint varLoc = glGetUniformLocation(shaderProgramID, variableName.c_str());

	glUniform1f(varLoc, value);
}

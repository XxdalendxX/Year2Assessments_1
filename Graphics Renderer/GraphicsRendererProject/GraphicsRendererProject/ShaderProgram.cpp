#include "ShaderProgram.h"
#include "Utilities.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
}

void ShaderProgram::LoadFromFiles(std::string vertexShaderName, std::string fragmentShaderName)
{
	loadedProperly = true;

	//Assigns VertexShaderID as a newly created vertex shader.
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//Assigns FragmentShaderID as a newly created fragment shader.
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Assigns the ShaderProgramID as a newly created program.
	shaderProgramID = glCreateProgram();

	//The string as a result of the vertex shader code being read
	std::string vertexSource = LoadFileAsString(vertexShaderName);
	//The string as a result of the vertex shader code being read
	std::string fragmentSource = LoadFileAsString(fragmentShaderName);

	//vertex shader code converted to a C string
	const char* vertexSourceC = vertexSource.c_str();

	//Replaces the source code of the shader (shader source, elements in string and length arrays, shader code, array of string lengths)
	glShaderSource(vertexShaderID, 1, &vertexSourceC, nullptr);
	//compiles the shader
	glCompileShader(vertexShaderID);

	//sets up error log and success status of compiled shaders
	GLchar errorLog[555];
	GLint successStatus = 0;
	//checks the compile status of the vertex shader and returns the outcome
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

	//fragment shader code converted to a C string
	const char* fragmentSourceC = fragmentSource.c_str();

	//Replaces the source code of the shader (shader source, elements in string and length arrays, shader code, array of string lengths)
	glShaderSource(fragmentShaderID, 1, &fragmentSourceC, nullptr);
	//Compiles the shader
	glCompileShader(fragmentShaderID);

	//Checks the compile status of the fragment shader and returns the outcome
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

	//Attaches the vertex shader to the shader program
	glAttachShader(shaderProgramID, vertexShaderID);
	//Attaches the fragment shader to the shader program
	glAttachShader(shaderProgramID, fragmentShaderID);
	//Links the program
	glLinkProgram(shaderProgramID);

	//Checks if the program successfully linked and returns outcome
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &successStatus);

	if (successStatus == GL_FALSE)
	{
		std::cout << "Ah well... Shader link has been unsuccessfully completed for one reason or another." << std::endl;
		glGetShaderInfoLog(shaderProgramID, 555, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedProperly = false;
	}

	//Returns console text if everything compiled and linked properly
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
	glDetachShader(shaderProgramID, vertexShaderID);
	glDetachShader(shaderProgramID, fragmentShaderID);
	glDeleteProgram(shaderProgramID);
}

void ShaderProgram::SetFloatUniform(std::string variableName, float value)
{
	GLint varLoc = glGetUniformLocation(shaderProgramID, variableName.c_str());

	glUniform1f(varLoc, value);
}

void ShaderProgram::SetMatrixUniform(std::string variableName, glm::mat4 value)
{
	GLint varLoc = glGetUniformLocation(shaderProgramID, variableName.c_str());

	glUniformMatrix4fv(varLoc, 1, GL_FALSE, &value[0][0]);
}
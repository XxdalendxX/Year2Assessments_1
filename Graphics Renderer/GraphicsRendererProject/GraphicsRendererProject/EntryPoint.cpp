#include "Graphics.h"
#include "Maths.h"
#include "Utilities.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	//Initialise GLFW, have to make sure it works.
	if (!glfwInit())
	{
		return -1;
	}

	//Set resolution and application name here.
	window = glfwCreateWindow(1280, 720, "I will indeed copy this", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//This will tell GFLW that the window created is what should be rendered to
	glfwMakeContextCurrent(window);

	//Tell GLAD to load all it's OpenGL functions
	if (!gladLoadGL())
	{
		glfwTerminate();
		return -1;
	}

	printf("OpenGL version %i.%i\n", GLVersion.major, GLVersion.minor);

	ShaderProgram simpleShader;
	simpleShader.LoadFromFiles("shader.vert", "shader.frag");

	Mesh object;
	object.CreatePyramid();

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0, 1);

	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		simpleShader.Enable();

		//allows for the rotation of or around the object
		mat4 rotation = glm::rotate(mat4(1), (float)glfwGetTime(), vec3(0, 1, 0));

		//where the camera is placed and facing
		mat4 view = glm::lookAt(vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 1, 0));

		float aspect;
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		aspect = width / (float)height;


		glm::mat4 projection = glm::perspective(3.14159f / 4, aspect, 1.0f, 100.0f);

		simpleShader.SetMatrixUniform("transformMatrix", projection * view * rotation);

		object.Bind();
		object.Render();
		object.Unbind();

		//Swapping the buffers - means current frame is over
		glfwSwapBuffers(window);
		//Tell GLFW to check for current imputs/events.
		glfwPollEvents();
	}

	//At this point the window should close and clean up of GLFW and exiting goes here
	glfwTerminate();
	return 0;
}
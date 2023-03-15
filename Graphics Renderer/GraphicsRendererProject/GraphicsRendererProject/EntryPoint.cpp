#include "Graphics.h"
#include "Utilities.h"
#include "DebugCallback.h"
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	//Initialise GLFW, have to make sure it works.
	if (!glfwInit())
	{
		return -1;
	}
/*
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
*/
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

	float red = 0.5f;
	float green = 0.0f;
	float blue = 0.5f;

	std::cout << LoadFileAsString("BigBrianText.txt") << std::endl;

	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen - to do rendering later
		glClear(GL_COLOR_BUFFER_BIT);

		//Gets the cursor position and then assigns the window colour accordingly  
		double cursorX, cursorY;
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwGetCursorPos(window, &cursorX, &cursorY);
		red = float(cursorX) / width;
		green = float(cursorY) / height;
		blue = (red + green) / 2;
		glClearColor(red, green, blue, 1.0);

		//Swapping the buffers - means current frame is over
		glfwSwapBuffers(window);

		//Tell GLFW to check for current imputs/events.
		glfwPollEvents();
/*
#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(nullptr, nullptr);
#endif
*/
	}

	//At this point the window should close and clean up of GLFW and exiting goes here
	glfwTerminate();
	return 0;
}
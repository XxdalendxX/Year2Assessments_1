//These includes are specific to the way that gGLFW and GLAD has been set up
#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#include "glad.h"

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
		return -1;
	}

	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen - to do rendering later
		glClear(GL_COLOR_BUFFER_BIT);
		//Swapping the buffers - means current frame is over
		glfwSwapBuffers(window);
		//Tell GLFW to check for current imputs/events.
		glfwPollEvents();
	}

	//At this point the window should close and clean up of GLFW and exiting goes here
	glfwTerminate();
	return 0;
}
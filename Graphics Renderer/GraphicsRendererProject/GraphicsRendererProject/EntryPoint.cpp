#include "Graphics.h"
#include "Maths.h"
#include "Utilities.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "Texture.h"
#include "Text.h"
#include "Time.h"

void ObjectRender(Mesh& object);
void ImGuiRender();
int Initialise(GLFWwindow* window);

GLFWwindow* window;
int main(void)
{
	if (Initialise(window) < 0)
		return -1;

	printf("OpenGL version %i.%i\n", GLVersion.major, GLVersion.minor);

	//ImGui initialisation
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ShaderProgram phongShader;
	phongShader.LoadFromFiles("phongShader.vert", "phongShader.frag");

	Camera cam;

	Light light1;
	vec3 ambientLight;

	Texture texture("Obamium.png");
	Mesh objectA;
	Mesh objectB;
	objectA.CreatePyramid();
	objectB.InitialiseFromFile("stanford/bunny.obj");
	objectB.LoadMaterial("stanford/bunny.mtl");

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1);


	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		phongShader.Enable();

		float time = glfwGetTime(); //gets time since application start
		light1.direction = glm::normalize(vec3(glm::cos(time * 2), 0, glm::sin(time * 2)));
		//light1.direction = glm::normalize(vec3(0, 1, 1));
		light1.colour = { 1,0,1 };
		ambientLight = {0.25f, 0.25f, 0.25f};

		//allows for the rotation of or around the object
		mat4 rotation = glm::rotate(mat4(1), 1.0f, vec3(0, 1, 0));

		//where the camera is placed and facing
		
		cam.Update(delta, window);
		//mat4 view = glm::lookAt(vec3(6, 6, 6), vec3(0, 2, 0), vec3(0, 1, 0));
		mat4 view = cam.GetViewMatrix();

		float aspect;
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		aspect = width / (float)height;

		//Projection Matrix
		mat4 projection = cam.GetProjectionMatrix(aspect);

		//Movement vs Perspective Matrix
		mat4 mvpMatrix = projection * view * rotation;

		phongShader.SetMatrixUniform("mvpMatrix", mvpMatrix);
		phongShader.SetMatrixUniform("mMatrix", rotation);		//mMatrix = model matrix
		phongShader.SetVectorUniform("lightDirection", light1.direction);
		phongShader.SetVectorUniform("lightColour", light1.colour);
		phongShader.SetVectorUniform("ambientLight", ambientLight);

		//Set the texture sampler uniform to the value corresponding to the active texture,
		//NOT the texture ID.
		objectB.ApplyMaterial(&phongShader);
		phongShader.SetIntergerUniform("textureSampler", 1);

		texture.Bind(1);

		ObjectRender(objectA);
		ObjectRender(objectB);

		//done from texture class to avoid errors from
		Texture::Unbind(1);

		ImGuiRender();

		//Swapping the buffers - means current frame is over
		glfwSwapBuffers(window);
		//Tell GLFW to check for current imputs/events.
		glfwPollEvents();

	}

	//At this point the window should close and clean up of GLFW and exiting goes here
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}

int Initialise(GLFWwindow* window)
{
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

	return 0;
}

void ObjectRender(Mesh& object)
{
	object.Bind();
	object.Render();
	object.Unbind();
}


void ImGuiRender()
{
	ImGui::Render();

	if (ImGui::GetDrawData())
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
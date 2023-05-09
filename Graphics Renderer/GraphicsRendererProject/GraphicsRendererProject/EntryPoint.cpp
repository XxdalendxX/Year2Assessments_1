#include "Graphics.h"
#include "ImGui_Class.h"
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

GLFWwindow* window;
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

	//ImGui initialisation
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ShaderProgram phongShader;
	phongShader.LoadFromFiles("phongShader.vert", "phongShader.frag");

	Camera cam;

	Light light1;
	Light light2;
	vec3 ambientLight;

	Texture texture1("Obamium.png");

	Mesh objectA;
	Mesh objectB;
	objectA.CreatePyramid();
	objectB.InitialiseFromFile("soulspear/soulspear.obj");
	objectB.LoadMaterial("soulspear/soulspear.mtl");

	light1.direction = glm::normalize(vec3(0, 1, 1));
	light1.colour = { 1,1,1 };
	
	light2.colour = { 1,1,1 };

	ambientLight = { 0.25f, 0.25f, 0.25f };

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1);

	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//creates new ImGui frame
		UINewFrame();

		

		phongShader.Enable();

		float time = glfwGetTime(); //gets time since application start
		light2.direction = glm::normalize(vec3(glm::cos(time * 2), 0, glm::sin(time * 2)));

		//ImGui Menu within application
		ImGui::Begin("Light Settings");
		ImGui::DragFloat3("Sunlight Direction", &light1.direction[0], 0.1f, -1.0f, 1.0f);
		ImGui::DragFloat3("Sunlight Colour", &light1.colour[0], light1.colour.x, light1.colour.y, light1.colour.z);
		ImGui::DragFloat3("Point Light Colour", &light2.colour[0], light1.colour.x, light1.colour.y, light1.colour.z);
		ImGui::End();

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
		phongShader.SetVectorUniform("cameraPos", cam.GetPos());
		phongShader.SetVectorUniform("lightDirection2", light2.direction);
		phongShader.SetVectorUniform("lightColour2", light2.colour);
		phongShader.SetVectorUniform("lightDirection1", light1.direction);
		phongShader.SetVectorUniform("lightColour1", light1.colour);
		phongShader.SetVectorUniform("ambientLight", ambientLight);

		/*Set the texture sampler uniform to the value corresponding
		to the active texture NOT the texture ID.*/
		phongShader.SetIntergerUniform("textureSampler", 0);

		texture1.Bind(0);
		ObjectRender(objectA);
		//done from texture class to avoid errors
		Texture::Unbind(0);

		objectB.ApplyMaterial(&phongShader);
		ObjectRender(objectB);
		Texture::Unbind(0);

		//renders ImGui objects frame
		UIRender();

		//ends current ImGui frame
		UIEndFrame();
		//Swapping the buffers - means current frame is over
		glfwSwapBuffers(window);
		//Tell GLFW to check for current imputs/events.
		glfwPollEvents();

	}
	UIShutDown();
	//At this point the window should close and clean up of GLFW and exiting goes here
	glfwTerminate();
	return 0;
}

void ObjectRender(Mesh& object)
{
	object.Bind();
	object.Render();
	object.Unbind();
}

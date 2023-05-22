#include "Graphics.h"
#include "ImGui_Class.h"
#include "Maths.h"
#include "Utilities.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "SceneLights.h"
#include "Mesh.h"
#include "Texture.h"
#include "Text.h"
#include "Time.h"

//to communicate light data to the shaders
SceneLights m_Lights;
//to contain all the light data in one place
std::vector<Light> lightSources;

void ObjectRender(Mesh& object);
void Draw(ShaderProgram* shader, std::vector<Light> lightSources);

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

	Light frontLight({-3,2,-1}, {1,1,1}, 25);
	Light backLight({3,2,2}, {1,1,1}, 25);
	Light colourLight({ 0,6,0 }, { 0,4,0 }, 4);
	vec3 ambientLight({ 0.25f, 0.25f, 0.25f });

	Mesh objectA;
	objectA.InitialiseFromFile("soulspear/soulspear.obj");
	objectA.LoadMaterial("soulspear/soulspear.mtl");
	Mesh objectB;
	objectB.InitialiseFromFile("soulspear/soulspear.obj", vec3{2,0,2});
	objectB.LoadMaterial("soulspear/soulspear.mtl");
	Mesh objectC;
	objectC.InitialiseFromFile("soulspear/soulspear.obj", vec3{ -2,0,-2 });
	objectC.LoadMaterial("soulspear/soulspear.mtl");

	lightSources.push_back(frontLight);
	lightSources.push_back(backLight);
	lightSources.push_back(colourLight);

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1);

	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//creates new ImGui frame
		UINewFrame();

		phongShader.Enable();

		//ImGui Menu within application
		ImGui::Begin("Light Settings");
		ImGui::DragFloat3("Light1 Direction", &lightSources[0].direction[0], lightSources[0].direction.x, lightSources[0].direction.y, lightSources[0].direction.z);
		ImGui::DragFloat3("Light1 Colour", &lightSources[0].colour[0], lightSources[0].colour.x, lightSources[0].colour.y, lightSources[0].colour.z);
		ImGui::DragFloat3("Light2 Direction", &lightSources[1].direction[0], lightSources[1].direction.x, lightSources[1].direction.y, lightSources[1].direction.z);
		ImGui::DragFloat3("Light2 Colour", &lightSources[1].colour[0], lightSources[1].colour.x, lightSources[1].colour.y, lightSources[1].colour.z);
		ImGui::DragFloat3("Light3 Direction", &lightSources[2].direction[0], lightSources[2].direction.x, lightSources[2].direction.y, lightSources[2].direction.z);
		ImGui::DragFloat3("Light3 Colour", &lightSources[2].colour[0], lightSources[2].colour.x, lightSources[2].colour.y, lightSources[2].colour.z);
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
		phongShader.SetVectorUniform("ambientLight", ambientLight);

		Draw(&phongShader, lightSources);

		/*Set the texture sampler uniform to the value corresponding
		to the active texture NOT the texture ID.*/
		phongShader.SetIntergerUniform("textureSampler", 0);

		objectA.ApplyMaterial(&phongShader);
		ObjectRender(objectA);
		//done from texture class to avoid errors
		Texture::Unbind(0);
		 
		objectB.ApplyMaterial(&phongShader);
		ObjectRender(objectB);
		//done from texture class to avoid errors
		Texture::Unbind(0);
		
		objectC.ApplyMaterial(&phongShader);
		ObjectRender(objectC);
		//done from texture class to avoid errors
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

void Draw(ShaderProgram* shader, std::vector<Light> lightSources)
{
	m_Lights.PushBack(lightSources);
	
	int numLights = lightSources.size();
	shader->SetIntergerUniform("numLights", numLights);
	shader->SetVectorUniform("PointLightPosition", numLights, m_Lights.GetPointLightPositions());
	shader->SetVectorUniform("PointLightColour", numLights, m_Lights.GetPointLightColours());
}



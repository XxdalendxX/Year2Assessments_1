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

SceneLights m_Lights;

void ObjectRender(Mesh& object);
void Draw(ShaderProgram* shader);

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

	Light sunLight;
	Light pointLight;
	vec3 ambientLight;

	m_Lights.pointLights.push_back(sunLight);
	m_Lights.pointLights.push_back(pointLight);

	Texture texture1("Obamium.png");

	Mesh objectA;
	Mesh objectB;
	objectA.CreatePyramid();
	objectB.InitialiseFromFile("soulspear/soulspear.obj");
	objectB.LoadMaterial("soulspear/soulspear.mtl");

	sunLight.direction = glm::normalize(vec3(-1, -1, -1));
	sunLight.colour = { 0,1,0 };
	pointLight.direction = glm::normalize(vec3(1, 1, 1));
	pointLight.colour = { 1,0,1 };

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
		pointLight.direction = glm::normalize(vec3(glm::cos(time * 2), 0, glm::sin(time * 2)));

		//ImGui Menu within application
		ImGui::Begin("Light Settings");
		ImGui::DragFloat3("Sunlight Direction", &sunLight.direction[0], -1.0f, -1.0f, -1.0f);
		ImGui::DragFloat3("Sunlight Colour", &sunLight.colour[0], sunLight.colour.x, sunLight.colour.y, sunLight.colour.z);
		ImGui::DragFloat3("Point light Direction", &pointLight.direction[0], 1.0f, 1.0f, 1.0f);
		ImGui::DragFloat3("Point light Colour", &pointLight.colour[0], pointLight.colour.x, pointLight.colour.y, pointLight.colour.z);
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

		Draw(&phongShader);

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

void Draw(ShaderProgram* shader)
{
	for (int i = 0; i < MAX_LIGHTS && i < m_Lights.pointLights.size(); i++)
	{
		m_Lights.pointLightPositions[i] = m_Lights.pointLights[i].direction;
		m_Lights.pointLightColours[i] = m_Lights.pointLights[i].colour;
	}

	int numLights = m_Lights.GetNumLights();
	shader->SetIntergerUniform("numLights", numLights);
	shader->SetVectorUniform("PointLightPosition", numLights, m_Lights.GetPointLightPositions());
	shader->SetVectorUniform("PointLightColour", numLights, m_Lights.GetPointLightColours());
}



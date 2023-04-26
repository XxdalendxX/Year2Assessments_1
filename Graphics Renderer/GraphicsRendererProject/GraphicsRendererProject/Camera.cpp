#include "Camera.h"

Camera::Camera()
{
	m_theta = 220;
	m_phi = -20;
	m_position = { 4,4,4};
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime, GLFWwindow* window)
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	//calculate the x, y, and z axis for the camera
	vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	vec3 right(-sin(thetaR), 0, cos(thetaR));
	vec3 up(0, 1, 0);
	Inputs(deltaTime, window, up, right, forward);
}

void Camera::Inputs(float deltaTime, GLFWwindow* window, vec3 up, vec3 right, vec3 forward)
{
	float rotationSpeed = 100;
	//move up and down
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		m_position += 5.0f * up * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		m_position -= 5.0f * up * deltaTime;
	}

	//move left, right, forward, backwards
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_position += 10.0f * forward * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		m_position -= 10.0f * right * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		m_position -= 10.0f * forward * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		m_position += 10.0f * right * deltaTime;
	}

	//rotate camera, left, right, up, down
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		m_theta -= rotationSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		m_theta += rotationSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		m_phi += rotationSpeed * deltaTime;
		m_phi = Clamp(m_phi, -89, 89);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		m_phi -= rotationSpeed * deltaTime;
		m_phi = Clamp(m_phi, -89, 89);
	}
}

mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	
	return glm::lookAt(m_position, m_position + forward, vec3(0,1,0));
}

mat4 Camera::GetProjectionMatrix(float aspect)
{
	return glm::perspective(PI / 4, aspect, 0.1f, 1000.0f);
}

#include "Camera.h"

Camera::Camera()
{
	m_theta, m_phi = 0;
	m_position = { 1,1,1 };
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
}

void Camera::Inputs(float deltaTime, GLFWwindow* window, vec3 up, vec3 right, vec3 forward)
{
	//move up and down
	if (glfwGetKey(window, GLFW_KEY_X))
	{
		m_position += up * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_Z))
	{
		m_position -= up * deltaTime;
	}

	//move left, right, forward, backwards
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		m_position += forward * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		m_position -= right * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		m_position -= forward * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		m_position += right * deltaTime;
	}

	//rotate camera, left, right, up, down
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		m_position += forward * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		m_position -= right * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		m_position -= forward * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		m_position += right * deltaTime;
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

#pragma once
#include "Maths.h"
#include "Graphics.h"


class Camera
{
	float m_theta;
	float m_phi;
	vec3 m_position;

	

protected:

public:
	Camera();
	~Camera();

	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;

	void Update(float deltaTime, GLFWwindow* window);

	void Inputs(float deltaTime, GLFWwindow* window, vec3 up, vec3 right, vec3 forward);

	mat4 GetViewMatrix();

	mat4 GetProjectionMatrix(float aspect);

	float r,g,b;
	
};
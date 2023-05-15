#pragma once

#include "Light.h"
#include "Maths.h"

const int MAX_LIGHTS = 4;

class SceneLights
{
public:
	std::vector<Light> pointLights;
	
	vec3 pointLightPositions[MAX_LIGHTS];
	vec3 pointLightColours[MAX_LIGHTS];

	int GetNumLights() { return (int)pointLights.size(); }
	vec3* GetPointLightPositions() { return &pointLightPositions[0]; }
	vec3* GetPointLightColours() { return &pointLightColours[0]; }
	std::vector<Light>& GetPointLights() { return pointLights; }
};
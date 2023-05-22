#pragma once

#include "Light.h"
#include "Maths.h"

const int MAX_LIGHTS = 4;

class SceneLights
{
public:	
	vec3 pointLightPositions[MAX_LIGHTS];
	vec3 pointLightColours[MAX_LIGHTS];

	vec3* GetPointLightPositions() { return &pointLightPositions[0]; }
	vec3* GetPointLightColours() { return &pointLightColours[0]; }

	void PushBack(std::vector<Light> lightSources)
	{
		for (int i = 0; i < lightSources.size(); i++)
		{
			pointLightPositions[i] = lightSources[i].direction;
			pointLightColours[i] = lightSources[i].colour;
		}
	}
};
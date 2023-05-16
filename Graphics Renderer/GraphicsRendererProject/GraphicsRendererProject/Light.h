#pragma once
#include "Maths.h"

struct Light
{
	vec3 direction;
	vec3 colour;

	Light();

	Light(vec3 position, vec3 col, float intensity)
	{
		direction = position;
		colour = col * intensity;
	}
};
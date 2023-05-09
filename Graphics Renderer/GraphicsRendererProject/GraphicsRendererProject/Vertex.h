#pragma once
#include "Maths.h"
#include "Graphics.h"

struct Vertex
{
	vec3 position; //Cartesian coordiantes of the vertex 
	vec3 normal; //Normal of the vertex
	vec2 uv; //Texture coordinates with range of [0,1] and [u,v]
	vec3 colour; //RGB of the vertex (will blend between other vertices)

	//Enables vertex attribute arrays and set vertex attribute pointers for the 4 variables
	static void SetUpAttributes();
};

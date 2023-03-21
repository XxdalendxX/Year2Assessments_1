#version 450

out vec4 FragColour;

in vec3 _colour;

void main()
{
	FragColour = vec4(_colour, 1);
}
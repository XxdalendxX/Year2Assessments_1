#version 450

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Colour;

uniform mat4 transformMatrix;

out vec3 _colour;

void main()
{
	gl_Position = transformMatrix * vec4(Position * 0.5, 1);
	_colour = Colour;
}
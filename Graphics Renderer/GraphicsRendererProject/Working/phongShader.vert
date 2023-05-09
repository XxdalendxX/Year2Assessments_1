#version 450

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UVs;
layout (location = 3) in vec3 Colour;

uniform mat4 mvpMatrix;
uniform mat4 mMatrix;

out vec4 _Position;
out vec3 _Colour;
out vec3 _Normal;
out vec2 _UVs;

void main()
{
	gl_Position = mvpMatrix * vec4(Position * 0.5, 1);
	_Position = mMatrix * vec4(Position * 0.5, 1);
	_Colour = Colour;
	_UVs = UVs;
	_Normal = (mMatrix * vec4(Normal, 0)).xyz;
}
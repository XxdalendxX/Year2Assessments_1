#version 450

out vec4 FragColour;

in vec3 _Colour;
in vec3 _Normal;
in vec2 _UVs;

uniform vec3 lightDirection;

uniform sampler2D textureSampler;

void main()
{
	vec3 diffuseColour = texture(textureSampler, _UVs).xyz;
	float lightValue = clamp(dot(-lightDirection, _Normal), 0.0, 1.0);
	lightValue += 0.1;
	FragColour = vec4(diffuseColour * lightValue, 1.0);
	
}
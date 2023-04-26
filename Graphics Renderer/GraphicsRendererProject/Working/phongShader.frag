#version 450

out vec4 FragColour;

in vec4 _Position;
in vec3 _Colour;
in vec3 _Normal;
in vec2 _UVs;

uniform vec3 cameraPos;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 ambientColour;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform sampler2D textureSampler;

void main()
{
	//Ensure normal and light direction are normalised
	vec3 N = normalize(_Normal);
	vec3 L = normalize(lightDirection);
	
	//Calculate lambert term (negate light direction)
	float lambertTerm = max(0, min(1, dot(N, -L)));

	//Calculate view vector and reflection vector
	vec3 V = normalize(cameraPos - _Position.xyz);
	vec3 R = reflect(L, N);

	//Calculate specular term
	float specularTerm = pow( max(0, dot(R, V)), specularPower);

	//Calculate each colour property
	vec3 ambient = ambientColour * Ka;
	vec3 diffuse = lightColour * Kd * lambertTerm;
	vec3 specular = lightColour * Ks * specularTerm;

	FragColour = vec4(diffuse + ambient + specular, 1.0);
	
}
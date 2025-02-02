#version 450

out vec4 FragColour;

in vec4 _Position;
in vec3 _Colour;
in vec3 _Normal;
in vec2 _UVs;
in vec3 _Tangent;
in vec3 _BiTangent;

uniform vec3 cameraPos;

uniform vec3 lightDirection;
uniform vec3 lightColour;

const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 PointLightColour[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform vec3 ambientColour;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform sampler2D textureSampler;
uniform sampler2D textureSpec;
uniform sampler2D textureNorm;

vec3 getDiffuse(vec3 direction, vec3 colour, vec3 normal);
vec3 getSpecular (vec3 direction, vec3 colour, vec3 normal, vec3 view);

vec3 diffuseTotal;
vec3 specularTotal;

void main()
{
	//Ensure normal and light direction are normalised
	vec3 N = normalize(_Normal);
	vec3 T = normalize(_Tangent);
	vec3 B = normalize(_BiTangent);
	vec3 L = normalize(lightDirection);

	mat3 TBN = mat3(T,B,N);

	vec3 texDiff = texture(textureSampler, _UVs).rgb;
	vec3 texSpec = texture(textureSpec, _UVs).rgb;
	vec3 texNorm = texture(textureNorm, _UVs).rgb;

	N = TBN * (texNorm * 2 - 1);
	
	//Calculate view vector
	vec3 V = normalize(cameraPos - _Position.xyz);
	
	for (int i = 0; i < numLights; i++)
	{
		vec3 direction =_Position.xyz - PointLightPosition[i];
		float distance = length(direction);
		direction = direction / distance;

		//Attenuate the light intensity with inverse square law
		vec3 colour = PointLightColour[i] / (distance * distance);

		//Calculate diffuse lighting from sunlight
		diffuseTotal += getDiffuse (direction, colour, N);
		
		//Calculate specular light from directional light
		specularTotal += getSpecular(direction, colour, N, V);
	}
	
	//Calculate each colour property
	vec3 ambient = ambientColour * Ka * texDiff;
	vec3 diffuse = Kd * diffuseTotal * texDiff;
	vec3 specular = Ks * texSpec * specularTotal;
	
	FragColour = vec4(diffuse + ambient + specular, 1.0);
	//vec4(N, 1.0);
	//vec4(diffuse + ambient + specular, 1.0);
	//texture(textureSampler, _UVs);
	
}


vec3 getDiffuse(vec3 direction, vec3 colour, vec3 normal)
{
	return colour * max(0, dot(normal, -direction));
}

vec3 getSpecular (vec3 direction, vec3 colour, vec3 normal, vec3 view)
{
	vec3 R = reflect(direction, normal);
	float specularTerm = pow(max(0, min(0, dot(R, view))), specularPower);
	return specularTerm * colour;
}

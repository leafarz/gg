#shader vertex
#version 330 core

#include "common.glh"

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 color;

out vec3 vcolor;
out DATA
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	vec3 color;
} vs_out;


uniform mat4 sys_MVP;
uniform mat4 sys_M;

void main()
{
    gl_Position = sys_MVP * vec4(position.x, position.y, position.z, 1.0);
	vs_out.position = (sys_M * vec4(position,1)).xyz;
	vs_out.normal = (sys_M * vec4(normal,0)).xyz;
	vs_out.color = color;
	vs_out.uv = vec2(uv.x, 1-uv.y);
}


#shader fragment
#version 330 core

#include "common.glh"

in DATA
{
	vec3 position;
	vec2 uv;
	vec3 normal;
	vec3 color;
} fs_in;

out vec4 fcolor;

struct Light
{
	vec4 position;
	vec3 direction;
	vec4 color;
	float intensity;
	
	float constantAttenuation;
	float linearAttenuation;
	float exponentAttenuation;

	float radius;
	float angle;	// spotCutoff
};

uniform Light lights[MAX_LIGHTS];

uniform sampler2D test;
uniform vec3 sys_AmbientColor;
uniform float sys_Time;

float fresnel(vec3 direction, vec3 normal)
{
	return max(dot(direction, -normal),0);
}

vec3 computeDirectionalLight(Light light, vec3 surfaceNormal)
{
	return light.color.xyz * fresnel(light.direction, surfaceNormal);
}

vec3 computePointLight(Light light, vec3 surfacePos)
{
	vec3 _posToLight = light.position.xyz - surfacePos;
	float _posToLightDist = length(_posToLight);

	float _atten = 1.0 / (
		light.constantAttenuation +
		light.linearAttenuation * _posToLightDist +
		light.exponentAttenuation * _posToLightDist * _posToLightDist +
		0.00001
	);
	return light.color.xyz * _atten;
}

vec3 computeSpotLight(Light light, vec3 surfacePos)
{
	vec3 _posToLight = light.position.xyz - surfacePos;
	vec3 _posToLightDir = normalize(_posToLight);
	float _angle = cos(radians(light.angle));
	float _dot = fresnel(light.direction, _posToLightDir);

	// if within cone
	if(_dot > _angle)	// equivalent to: acos(_dot) < radians(angle)
	{
		float _posToLightDist = length(_posToLight);
		float _spotFactor = (_dot - _angle) / _angle;
		float _atten = 1.0 / (
			light.constantAttenuation +
			light.linearAttenuation * _posToLightDist +
			light.exponentAttenuation * _posToLightDist * _posToLightDist +
			0.00001
		);
		return light.color.xyz * _spotFactor * _atten;
	}
	else
	{
		return vec3(0,0,0);
	}
}
void main()
{
	vec3 _result;
	for(int i=-1; ++i < MAX_LIGHTS; )
	{
		// directional light
		if(lights[i].position.w == 0)
		{
			_result = _result + computeDirectionalLight(lights[i], fs_in.normal);
		}
		// point or spotlight
		else
		{
			// spotlight
			if (lights[i].angle < 90.0)
			{
				_result = _result + computeSpotLight(lights[i], fs_in.position.xyz);
			}
			else
			{
				_result = _result + computePointLight(lights[i], fs_in.position.xyz);
			}
		}
	}
	fcolor = max(vec4(_result,1), vec4(sys_AmbientColor,1));
}

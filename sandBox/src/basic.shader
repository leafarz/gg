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

void main()
{
	vec3 _result;

	float _atten;
	for(int i=-1; ++i < MAX_LIGHTS; )
	{
		float _diff;
		vec3 _lightDir;

		// directional light
		if(lights[i].position.w == 0)
		{
			_atten = 1;
			_lightDir = lights[i].direction;
		}
		// point or spotlight
		else
		{
			vec3 _posToLight = lights[i].position.xyz - fs_in.position;
			float _posToLightDist = length(_posToLight);

			_atten = 1.0 / (
				lights[i].constantAttenuation +
				lights[i].linearAttenuation * _posToLightDist +
				lights[i].exponentAttenuation * _posToLightDist * _posToLightDist +
				0.00001
			);
		}

		// _result = _result + lights[i].color.xyz * max(dot(fs_in.normal, -_lightDir), 0);
		_result = _result + _atten * lights[i].color.xyz;
	}
	fcolor = vec4(_result,1) + vec4(sys_AmbientColor,1);
}

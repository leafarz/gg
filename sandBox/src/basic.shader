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
	vec2 uv;
	vec3 normal;
	vec3 color;
} vs_out;


uniform mat4 sys_MVP;
uniform mat4 sys_M;

void main()
{
    gl_Position = sys_MVP * vec4(position.x, position.y, position.z, 1.0);
	vs_out.normal = (sys_M * vec4(normal,0)).xyz;
	vs_out.color = color;
	vs_out.uv = vec2(uv.x, 1-uv.y);
}


#shader fragment
#version 330 core

in DATA
{
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

uniform sampler2D test;

uniform vec3 lightDir = vec3(0,0,1);
uniform vec3 sys_AmbientColor;
float intensity = 0.5;
vec3 lightColor = vec3(1,0,0);

void main()
{
	float _diff = max(dot(fs_in.normal, -lightDir), 0);
	fcolor = texture(test, fs_in.uv) * _diff * intensity + vec4(sys_AmbientColor,1);
}
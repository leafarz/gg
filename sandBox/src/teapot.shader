#shader vertex
#version 330 core

#include "types.glh"

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
uniform float sys_Time;

void main()
{
    gl_Position = sys_MVP * vec4(position.x, position.y, position.z, 1.0) + vec4(normal * sin(sys_Time)*0.5,1);
	vs_out.normal = normalize((sys_M * vec4(normal,0)).xyz);
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

vec3 lightDir = vec3(0,0,1);
void main()
{
	float _diff = max(dot(fs_in.normal, -lightDir), 0.1);
	fcolor = vec4(fs_in.normal * _diff,1);

}
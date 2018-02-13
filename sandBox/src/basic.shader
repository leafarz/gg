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
	vec3 color;
} vs_out;


uniform mat4 sys_MVP;

void main()
{
    gl_Position = sys_MVP * vec4(position.x, position.y, position.z, 1.0);
	vs_out.color = color;
	vs_out.uv = vec2(uv.x, 1-uv.y);
}


#shader fragment
#version 330 core

in DATA
{
	vec2 uv;
	vec3 color;
} fs_in;

out vec4 fcolor;

struct TestStruct1
{
	float intensity;
	vec3 pos;
};
struct TestStruct2
{
	TestStruct1 ts1;
	vec3 color;
};
uniform float floatTest = 1;
uniform TestStruct2 ts2;
uniform vec3 v3Test= vec3(0,0,0);

uniform sampler2D test;
uniform sampler2D test2;


void main()
{
	// float val = floatTest + v3Test.x * v3Test.y * v3Test.z + ts2.color.x + ts2.color.y + ts2.color.z + ts2.ts1.intensity;
	//fcolor = vec4(1.0f, 0.5f, 0.2f, val);
	// fcolor = vec4(vcolor.x, vcolor.y, vcolor.z, 1);
	//fcolor = vec4(1.0f, GetX(tl), 0.2f, GetX(tl));
	
	// fcolor = vec4(fs_in.color,1);

	if(fs_in.uv.x < 0.5)
		fcolor = texture(test, fs_in.uv);
	else
		fcolor = texture(test2, fs_in.uv);

}
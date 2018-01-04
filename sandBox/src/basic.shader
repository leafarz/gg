#shader vertex
#version 330 core

#include "common.glh"

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}

#shader fragment
#version 330 core
out vec4 color;

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

void main()
{
	float val = floatTest + v3Test.x * v3Test.y * v3Test.z + ts2.color.x + ts2.color.y + ts2.color.z + ts2.ts1.intensity;
	color = vec4(1.0f, 0.5f, 0.2f, val);
	//color = vec4(1.0f, GetX(tl), 0.2f, GetX(tl));
}
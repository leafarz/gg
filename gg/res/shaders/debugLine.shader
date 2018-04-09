#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out DATA
{
	vec4 color;
} vs_out;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	vs_out.color = color;
}


#shader fragment
#version 330 core

in DATA
{
	vec4 color;
} fs_in;

void main()
{
	gl_FragColor = fs_in.color;
}
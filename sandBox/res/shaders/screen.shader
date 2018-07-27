#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out DATA
{
	vec2 uv;
} vs_out;

void main()
{
	vs_out.uv = uv;

	gl_Position = vec4(
		position.x,
		position.y,
		0.0, 1.0
	);
}

#shader fragment
#version 330 core

in DATA
{
	vec2 uv;
} fs_in;

out vec4 fcolor;

uniform sampler2D sys_ColorTexture;
uniform sampler2D sys_DepthTexture;

float depth(sampler2D depthTexture, vec2 uv)
{
	return texture(depthTexture, uv).b;
}

/* Returns the distance of current pixel to camera. */
float linearDepth(float depth,float near, float far)
{
	float _normalizedDepth = 2.0 * depth - 1.0;
	float _linearDepth = 2.0 * near * far / (far + near - _normalizedDepth * (far - near));
	return _linearDepth;
}

void main()
{
	vec3 _col = texture(sys_ColorTexture, fs_in.uv).rgb;
	float _depth = depth(sys_DepthTexture, fs_in.uv);

	fcolor = vec4(_col, 1.0);
}
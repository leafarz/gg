#shader vertex
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out DATA
{
	vec2 uv;
} vs_out;

uniform float mode;

void main()
{
	vs_out.uv = uv;

	float xScale = 0.4;
	float yScale = 0.4;

	if(mode == 0)
	{
		gl_Position = vec4(
			position.x*xScale - (1-xScale),
			position.y*yScale + (1-yScale),
			0.0, 1.0
		);     
	}
	else
	{
		gl_Position = vec4(
			position.x*xScale - (1-xScale),
			position.y*yScale - (1-yScale),
			0.0, 1.0
		);     
	}
	
}  

#shader fragment
#version 330 core

in DATA
{
	vec2 uv;
} fs_in;

out vec4 fcolor;

uniform sampler2D sys_ScreenTexture;
uniform sampler2D sys_DepthTexture;

uniform float mode;

/* Returns the distance of current pixel to camera. */
float linearDepth(float depth,float near, float far)
{
	float _normalizedDepth = 2.0 * depth - 1.0;
	float _linearDepth = 2.0 * near * far / (far + near - _normalizedDepth * (far - near));
	return _linearDepth;
}

void main()
{
	if(mode == 0)
	{
		vec3 col = texture(sys_ScreenTexture, fs_in.uv).rgb;
		fcolor = vec4(col, 1.0);
	}
	else
	{
		float _depth = texture(sys_DepthTexture, fs_in.uv).b;
		float _near = 0.1;
		float _far = 100;
		float _range = _far - _near;
		float _linearDepth = linearDepth(_depth, _near, _far) / _range * 10;

		fcolor = vec4(_linearDepth,_linearDepth,_linearDepth, 1.0);
	}
} 
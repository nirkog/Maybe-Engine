#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 Color;
in vec3 FragPos;
in vec2 uvCoords;
flat in int tid;
in mat4 View;
in mat4 Proj;

uniform sampler2D u_Textures[32];
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;

void main()
{
	if(tid > -1)
		FragColor = texture(u_Textures[tid], uvCoords);
	else
		FragColor = Color;
}
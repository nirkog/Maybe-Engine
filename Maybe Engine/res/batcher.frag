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
	//vec3 lightPos = vec3(Proj * View * vec4(u_LightPos, 1));
//	float ambient = 1.0f;
//	vec3 normal = vec3(0, 0, 1);
//	vec3 lightDir = normalize(u_LightPos - FragPos);
//	float diff = max(dot(normal, lightDir), 0.0);
//	vec3 diffuse = diff * u_LightColor;

	if(tid > -1)
		FragColor = texture(u_Textures[tid], uvCoords);
	else
		FragColor = Color;

	//FragColor = vec4(FragColor.rgb * (ambient + diffuse), FragColor.a);
}
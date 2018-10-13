#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 Color;
in vec2 FragPos;
in vec2 uvCoords;
flat in int tid;

//uniform vec2 u_LightCenter = vec2(0, 0);
uniform sampler2D u_Textures[32];

void main()
{
	//float ambient = 0.05f;
	//float spotlight = exp(-7 * sqrt(pow(FragPos.x - u_LightCenter.x, 2) + pow(FragPos.y - u_LightCenter.y, 2))) * 15 + 1;
	//vec4 texturedColor = texture(u_Textures[tid], uvCoords);
	//vec3 rgbColor = texturedColor.xyz * ambient * spotlight;
	//FragColor = vec4(rgbColor.xyz, texturedColor.a);
	//FragColor.a = 1;

	if(tid > -1)
		FragColor = texture(u_Textures[tid], uvCoords);
	else
		FragColor = Color;
}
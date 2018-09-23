#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform bool textured;
uniform vec3 u_Color;
uniform sampler2D u_Texture;

void main()
{	
	if(textured)
		FragColor = texture(u_Texture, TexCoords);
	else
		FragColor = vec4(u_Color, 1);
}
#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float alfa;

void main()
{
	FragColor = mix(texture(ourTexture, texCoord), texture(ourTexture2, texCoord), alfa) * vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
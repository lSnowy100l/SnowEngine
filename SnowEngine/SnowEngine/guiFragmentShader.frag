#version 400 core

in vec2 pass_texCoords;

out vec4 fragColor;

uniform sampler2D texSampler;

void main()
{
	fragColor = texture(texSampler, pass_texCoords);
}
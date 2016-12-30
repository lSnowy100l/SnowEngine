#version 400 core

in vec2 position;
in vec2 texCoords;

uniform mat4 toPixelsMatrix;

out vec2 pass_texCoords;

void main()
{
	gl_Position = toPixelsMatrix * vec4(position, 0.0, 1.0);
	pass_texCoords = texCoords;
}
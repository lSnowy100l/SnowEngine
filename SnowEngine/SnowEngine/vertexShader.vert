#version 400 core

in vec3 position;

uniform mat4 chunkTranslationMatrix;
uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 projectionMatrix;

out vec3 colour;

void main()
{
	gl_Position = projectionMatrix * rotationMatrix * translationMatrix * chunkTranslationMatrix * vec4(position, 1.0);
	colour = vec3(position.x/32, position.y/32, position.z/32);
}
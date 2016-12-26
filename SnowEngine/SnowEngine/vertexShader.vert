#version 400 core

in uvec3 position;

uniform mat4 chunkTranslationMatrix;
uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 projectionMatrix;

out vec3 colour;

void main()
{
	gl_Position = projectionMatrix * rotationMatrix * translationMatrix * chunkTranslationMatrix * vec4(position, 1.0);
	vec3 posfloat = position;
	colour = vec3(posfloat.x/32, posfloat.y/32, posfloat.z/32);
}
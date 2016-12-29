#version 400 core

in uvec3 position;
in float ambientOcclusion;

uniform mat4 chunkTranslationMatrix;
uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 projectionMatrix;

out vec3 colour;

void main()
{
	vec4 worldPos = rotationMatrix * translationMatrix * chunkTranslationMatrix * vec4(position, 1.0);
	vec3 posfloat = position;
	float distance = length(worldPos.xz);
	gl_Position = projectionMatrix * worldPos - vec4(0.0, pow(distance/64, 2), 0.0, 0.0);
	colour = vec3(posfloat.x/32, posfloat.y/32, posfloat.z/32) * ((ambientOcclusion/4)+0.75);
}
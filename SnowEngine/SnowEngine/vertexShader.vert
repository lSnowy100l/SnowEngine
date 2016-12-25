#version 400 core

in vec3 position;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 projectionMatrix;

out vec3 colour;

void main()
{
	gl_Position = projectionMatrix * rotationMatrix * translationMatrix * vec4(position, 1.0);
	colour = vec3(position.x/2 + 0.5, position.y/2 + 0.5, position.z/2 + 0.5);
}
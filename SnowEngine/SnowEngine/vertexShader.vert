in vec3 position;

uniform mat4 translationMatrix;
uniform mat4 projectionMatrix;

out vec3 colour;

void main()
{
	gl_Position = vec4(position, 1.0) * translationMatrix * projectionMatrix;
	colour = vec3(position.x + 0.5, position.y + 0.5, position.z + 0.5);
}
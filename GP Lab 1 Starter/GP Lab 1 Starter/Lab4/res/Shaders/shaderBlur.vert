#version 130


out vec3 position;
out vec2 texCoord;
out vec3 normals;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
}
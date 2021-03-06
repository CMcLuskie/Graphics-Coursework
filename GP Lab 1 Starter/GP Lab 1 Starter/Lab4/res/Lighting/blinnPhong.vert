#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 transform;

out vec3 v_norm;
out vec3 v_pos; 

void main()
{
	v_norm = VertexNormal;
	v_pos = vec3(VertexPosition);
	gl_Position = transform * vec4(VertexPosition, 1.0);
}
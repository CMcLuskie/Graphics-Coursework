#version 400 

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 transform;

out VS_OUT {
    vec3 normal;
} vs_out;

out vec3 v_norm;
out vec4 v_pos; 

void main()
{
	vs_out.normal = VertexNormal;
	v_pos = vec4(VertexPosition, 1.0);
	gl_Position = transform * vec4(VertexPosition, 1.0);
}
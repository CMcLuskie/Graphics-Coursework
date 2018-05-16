#version 400

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

uniform float magnitude;
uniform float time;

vec4 Explode(vec4 position, vec3 normal)
{
    float magnitudeExplode = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitudeExplode; 
    return position + vec4(direction, 0.0);
} 

void GenerateLine(int index)
{
    gl_Position = Explode(gl_in[0].gl_Position, gs_in[index].normal); //sets positon in relation to the exploson vector
    EmitVertex();
    gl_Position = Explode(gl_in[0].gl_Position, gs_in[index].normal)
		+ vec4(gs_in[index].normal, 0.0) * magnitude;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}

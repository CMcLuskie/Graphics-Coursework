#version 400 

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
} gs_in[];

out vec2 TexCoords; 

uniform float time;



vec4 Explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;//sets size to explode by
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; //sets the direction of the explosion
    return position + vec4(direction, 0.0); //returns the position in relation to the direction
} 

//gets position normals
vec3 normal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position); 
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
} 

//sets position of the geometry
void main() {    
    vec3 normal = normal();

    gl_Position = Explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;
    EmitVertex();
    gl_Position = Explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = Explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();
}  


#version 330 core

layout(location = 0) out FragColor
in vec3 Normal; 
in vec3 FragPos;  

uniform vec3 lightPos;  

void main()
{
   vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos - FragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * lightColor;
vec3 result = (ambient + diffuse) * objectColor;
FragColor = vec4(result, 1.0);
} 
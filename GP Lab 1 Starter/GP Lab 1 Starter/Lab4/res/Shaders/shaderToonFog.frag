#version 400

layout (location = 0) out vec4 fragcolor;

in vec3 v_norm;
in vec4 v_pos; 

uniform vec3 lightDir;
uniform vec3 fogColor;

uniform mat4 u_pm; 
uniform mat4 u_vm; 

uniform float zpos;

uniform float maxDist; //fog max distance
uniform float minDist; //fog min distance

vec3 ToonRim() {
 
  vec3 n = normalize(mat3(u_vm) * v_norm);      // convert normal to view space
  vec3 p = vec3((u_pm) * v_pos);                // position in clip space
  vec3 v = normalize(-p);                        // normalised eye vector
  float vdn = 1.0 - max(dot(v, n), 0.0);        // the rim contribution
 
 	float intensity;
	vec4 color;
	intensity = dot(lightDir,v_norm);//sets intensity using the dot product

		//sets final toon colour in relationt othe intensity
	if (intensity > 0.95)
		color = vec4(0.6,0.5,0.5,1.0);
	else if (intensity > 0.5)
		color = vec4(0.5,0.3,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.4,0.2,0.2,1.0);
	else
		color = vec4(0.2,0.1,0.1,1.0);

  fragcolor.a = 0.4;
  return vec3(smoothstep(0.4, 0.6, vdn)) * color.xyz; 
 }

 void main() 
 {

float dist = abs( zpos ); //gets the distance by ensure the zpos is a positive value
float fogFactor = (maxDist - dist) / (maxDist - minDist); //gets the fog value using a formula thats explained in the report
fogFactor = clamp( fogFactor, 0.0, 1.0 ); // returns a value between 0 and 1 that is also closest to fogFactor
vec3 toonRim = ToonRim();

vec3 color = mix( fogColor, toonRim, fogFactor); //mixes the fogcolour, toon rim colour, and the fogfactor together
fragcolor = vec4(color, 1.0);

}



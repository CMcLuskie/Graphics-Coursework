#version 130

varying vec2 texCoord0;

uniform sampler2D diffuse;
uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main()
{
	vec4 textureColor = texture2D(diffuse, texCoord0);
	if(textureColor.a < 0.5)
		discard;


		vec2 tex_offset = 1.0 / textureSize(diffuse, 0); // gets size of single texel
    vec3 result = texture(diffuse, texCoord0).rgb * weight[0]; // current fragment's contribution
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(diffuse, texCoord0 + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(diffuse, texCoord0 - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(diffuse, texCoord0 + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(diffuse, texCoord0 - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }

	gl_FragColor = vec4(result, 1.0);
}
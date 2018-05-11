#version 120

varying vec2 texCoord0;

uniform sampler2D diffuse;

void main()
{
	vec4 textureColor = texture2D(diffuse, texCoord0);
	if(textureColor.a < 0.5)
		discard;

	gl_FragColor = texture2D(diffuse, texCoord0);
}

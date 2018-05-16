#version 120

varying vec2 texCoord0;

uniform sampler2D diffuse;

void main()
{
	vec4 textureColor = texture2D(diffuse, texCoord0);	//gets tecxture colour of a fragment at that coordinate


	if(textureColor.a < 0.5)						//Checks to see if colour is transparent
		discard;									//if it is then this discards the fragment

	gl_FragColor = texture2D(diffuse, texCoord0);//returns the frag colour
}

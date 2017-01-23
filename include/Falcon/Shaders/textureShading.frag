#version 120

varying vec4 fragmentColor;
varying vec2 fragmentPosition;
varying vec2 fragmentUV;

//out vec4 color;

uniform float time;
uniform sampler2D sampler;

void main()
{
    vec4 textureColor = texture2D(sampler, fragmentUV);

	gl_FragColor = fragmentColor * textureColor;
}

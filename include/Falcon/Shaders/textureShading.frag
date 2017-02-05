#version 120

varying vec4 fragmentColor;
varying vec2 fragmentPosition;
varying vec2 fragmentUV;


uniform vec4 color;
uniform sampler2D sampler;

void main()
{
    vec4 textureColor = texture2D(sampler, fragmentUV) * color;

	gl_FragColor = fragmentColor * textureColor;
}

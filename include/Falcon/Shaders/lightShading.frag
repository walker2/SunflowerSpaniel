#version 120

varying vec4 fragmentColor;
varying vec2 fragmentPosition;
varying vec2 fragmentUV;


void main()
{
    float distance = length(fragmentUV);

	gl_FragColor = vec4(fragmentColor.rgb, fragmentColor.a * (pow(0.01, distance) - 0.01));
}

#version 120

attribute vec2 vertexPosition;
attribute vec4 vertexColor;
attribute vec2 vertexUV;

varying vec4 fragmentColor;
varying vec2 fragmentPosition;
varying vec2 fragmentUV;

uniform mat4 P;

void main()
{
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragmentColor = vertexColor;
    fragmentPosition = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
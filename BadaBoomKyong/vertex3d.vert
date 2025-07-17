#version 460

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextCoords;
layout(location = 2) in vec3 vNormals;

uniform mat4 uMVP;
uniform vec2 uUV_Offset;
uniform vec2 uUV_Scale;
out vec2 UV;

void main()
{
   gl_Position = uMVP * vPosition;   
   UV=vTextCoords*uUV_Scale+uUV_Offset;
}
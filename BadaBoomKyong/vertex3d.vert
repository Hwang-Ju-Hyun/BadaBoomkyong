#version 460

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTextCoords;
layout(location = 2) in vec3 vNormals;

uniform mat4 uMVP;
uniform vec2 uUV_Offset;
uniform vec2 uUV_Scale;
out vec2 UV;

void main()
{
   gl_Position = uMVP * vec4(vPosition, 1.0);   
   UV=vTextCoords*uUV_Scale+uUV_Offset;
}
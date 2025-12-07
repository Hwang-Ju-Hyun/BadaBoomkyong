#version 460 core

layout (location = 0) in vec3 a_Position;
layout(location = 1) in vec2 vTextCoords;


uniform mat4 u_MVP;
uniform vec2 uUV_Offset;
uniform vec2 uUV_Scale;


out vec2 UV;

void main()
{	
	gl_Position = u_MVP*vec4(a_Position, 1.0);
	UV=vTextCoords;
}
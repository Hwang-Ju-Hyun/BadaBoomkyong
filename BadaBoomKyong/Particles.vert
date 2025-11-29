#version 460 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_MVP;


uniform mat4 u_MVP_Particle;

void main()
{	
	gl_Position = u_MVP_Particle*vec4(a_Position, 1.0);
}
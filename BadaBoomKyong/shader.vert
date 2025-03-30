#version 460

layout(location=0) in vec3 pos;

void main()
{
	glPosition=vec4(pos,1.f);
}
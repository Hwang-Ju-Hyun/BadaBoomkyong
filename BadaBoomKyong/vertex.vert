#version 460

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec3 fragcolor;

void main()
{
    gl_Position = vec4(pos, 1.f);    
    fragcolor = vec3(uv,0.f);
}
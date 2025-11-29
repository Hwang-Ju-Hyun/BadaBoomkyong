#version 460

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 uv;

uniform mat4 uMVP_2d;
out vec3 fragcolor;

void main()
{
    gl_Position = uMVP_2d * vPosition;   
    fragcolor = vec3(uv,0.f);
}
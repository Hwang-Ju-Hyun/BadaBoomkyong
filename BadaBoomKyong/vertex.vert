#version 460

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

uniform mat3 uModel_to_NDC;
out vec3 fragcolor;

void main()
{
    gl_Position = vec4(vec2(uModel_to_NDC*vec3(pos.xy,1.f)),0.f,1.f);
    fragcolor = vec3(uv,0.f);
}
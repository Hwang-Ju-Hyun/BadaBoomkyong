#version 460

in vec3 fragcolor;

out vec4 color;

void main()
{
    color = vec4(fragcolor, 1.0f); // 보간된 RGB 값 적용
}
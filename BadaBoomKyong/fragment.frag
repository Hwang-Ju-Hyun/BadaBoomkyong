#version 460

in vec3 fragcolor;
uniform vec4 uColor_2d;

out vec4 color;

void main()
{
    color = vec4(uColor_2d); // ������ RGB �� ����
}
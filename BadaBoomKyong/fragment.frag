#version 460

in vec3 fragcolor;
uniform vec4 uColor;

out vec4 color;

void main()
{
    color = vec4(uColor); // ������ RGB �� ����
}
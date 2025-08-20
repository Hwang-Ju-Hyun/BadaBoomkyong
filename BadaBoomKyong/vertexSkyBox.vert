#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uVP; // proj * view (translation ������ ��)

void main()
{
    TexCoords = aPos;               // ť�� ��ǥ�� �״�� direction���� ���
    vec4 pos = uVP * vec4(aPos, 1.0);
    gl_Position = pos.xyww;         // w �������� ���缭 ������ �ڿ� ��
}
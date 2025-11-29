#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uVP; // proj * view (translation 제거한 것)

void main()
{
    TexCoords = aPos;               // 큐브 좌표를 그대로 direction으로 사용
    vec4 pos = uVP * vec4(aPos, 1.0);
    gl_Position = pos.xyww;         // w 성분으로 맞춰서 무조건 뒤에 깔림
}
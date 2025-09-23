#version 460

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTextCoords;
layout(location = 2) in vec3 vNormals;
layout(location = 3) in vec3 vTangents;


uniform mat4 uMVP;
uniform vec2 uUV_Offset;
uniform vec2 uUV_Scale;
uniform mat4 uM2W;

out vec2 UV;
out vec3 WorldPosition;
out vec3 WorldNormal;
out mat3 tbnMat;

void main()
{
   gl_Position = uMVP * vec4(vPosition, 1.0);   
   UV=vTextCoords*uUV_Scale+uUV_Offset;

   WorldPosition=(uM2W * vec4(vPosition, 1.0)).xyz;
   WorldNormal=normalize((uM2W*vec4(vNormals,0.0)).xyz);

    // === ���� �������� TBN ��� === 
    //vec4(vTangents,0.0)���� 0.0�� ���� w=0�϶� �������θ�
    vec3 N = normalize((uM2W * vec4(vNormals, 0.0)).xyz);
    vec3 Tangent = normalize((uM2W * vec4(vTangents, 0.0)).xyz);
    vec3 Bitanget = normalize(cross(N, Tangent)); // ��ź��Ʈ�� cross�� ����

    tbnMat = mat3(Tangent, Bitanget, N); 
}
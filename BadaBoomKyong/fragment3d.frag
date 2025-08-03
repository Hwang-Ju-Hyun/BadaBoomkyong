#version 460

out vec4 color;

uniform bool uIsCollider;
uniform bool uHasTexture;
uniform sampler2D uOutTexture;

in vec2 UV;

void main()
{
    if (uHasTexture)
    {
        vec4 texColor = texture(uOutTexture, UV);
        color = texColor;
    }
    else
    {
        color = vec4(UV, 0.0, 1.0); // UV 색상 디버깅용
    }
}

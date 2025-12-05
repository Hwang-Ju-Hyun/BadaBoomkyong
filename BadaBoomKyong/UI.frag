#version 460 core
in vec2 UV;

out vec4 o_Color;

uniform vec4 u_Color;
uniform bool uHasTexture;
uniform sampler2D uOutTexture;

uniform vec2 uUV_Offset;
uniform vec2 uUV_Scale;


void main()
{	
    vec2 finalUV = uUV_Offset + UV * uUV_Scale;
    
	if (uHasTexture)
    {
        o_Color = texture(uOutTexture, finalUV);               
    }    
    else
    {
        o_Color  = u_Color;// UV 색상 디버깅용
    }
}
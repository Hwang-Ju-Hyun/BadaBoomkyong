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
	if (uHasTexture)
    {
        o_Color = texture(uOutTexture, UV);               
    }    
    else
    {
        o_Color  = u_Color;// UV 색상 디버깅용
    }
}
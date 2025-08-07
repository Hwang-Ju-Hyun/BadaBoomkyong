#version 460

out vec4 color;

uniform bool uIsCollider;
uniform bool uHasTexture;
uniform sampler2D uOutTexture;
uniform bool uHurtEffect;

in vec2 UV;

void main()
{
    if (uHasTexture)
    {
        vec4 texColor = texture(uOutTexture, UV);
        if(uHurtEffect)
        {
            if(texColor.a<1.f)               
                color = texColor;
            else                
                color=vec4(1.0,1.0,1.0,1.0);
        }
        else
        {        
            color = texColor;
        }
        
    }    
    else
    {
        color = vec4(UV, 0.0, 1.0); // UV 색상 디버깅용
    }
}

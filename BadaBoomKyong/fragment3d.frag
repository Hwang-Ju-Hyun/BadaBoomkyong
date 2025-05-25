#version 460

out vec4 color;
uniform bool uIsCollider;
uniform vec4 uDebugColor;
in vec2 UV;

void main()
{   
	if(uIsCollider)
		color=uDebugColor;
	else
		color = vec4(UV,0.0,0.0);
}
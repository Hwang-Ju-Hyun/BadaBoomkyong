#version 460

out vec4 color;
//uniform vec4 uColor;
in vec2 UV;

void main()
{   
	//uColor={0.0,0.0,0.0,0.0};
	color = vec4(UV,0.0,0.0);
}
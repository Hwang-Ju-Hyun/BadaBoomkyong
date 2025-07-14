#version 460

out vec4 color;
//uniform bool uIsCollider;
//uniform vec4 uDebugColor;

uniform bool uHasTexture;
uniform sampler2D uOutTexture;
in vec2 UV;

void main()
{   
	if(uHasTexture)	
		color = texture(uOutTexture, UV) * vec4(1.0, 1.0, 1.0, 1.0);
	else
		color = vec4(0.5,0.0,0.0,1.0);
	return;

	if(uHasTexture)	
		color = texture(uOutTexture,UV);	
	else
		color = vec4(0.5,0.0,0.0,1.0);
}
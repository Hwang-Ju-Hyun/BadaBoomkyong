#version 460

in vec2 UV;
in vec3 WorldPosition;
in vec3 WorldNormal;

out vec4 color;

uniform bool uIsCollider;
uniform bool uHasTexture;
uniform sampler2D uOutTexture;
uniform bool uHurtEffect;
uniform vec3 uCameraPosition;

struct Light
{
    int type;
    vec3 position; //������� ��������
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    //spotlight
    vec3 direction;
    float cutoffangle;
};

uniform vec3 uMp_Ambient;
uniform vec3 uMp_Diffuse;
uniform vec3 uMp_Specular;
uniform float uShininess;

uniform int uLightNumber;
uniform Light uLight[1];
uniform int uLightColorOn;

void main()
{    
    vec3 Phong=vec3(0.f,0.f,0.f);

    //ī�޶� ���⺤��
    vec3 viewDir=normalize(uCameraPosition-WorldPosition);

    //ǥ�鿡�� ��������
    vec3 light_dir;

    for(int i=0;i<uLightNumber;i++)
    {       
        //POINT TYPE
        if(uLight[i].type==0)
        {
            light_dir = normalize(uLight[i].position-WorldPosition);            
        }
        //DIRECTIONAL TYPE
        else if(uLight[i].type==1)
        {
            light_dir = normalize(uLight[i].position);
        }
        //SPOTLIGHT TYPE
        else if(uLight[i].type==2)
        {
             light_dir=normalize(uLight[i].position-WorldPosition);
             
             //uLight[i].direction ����ȭ ��Ų ����:
             //light_dir��ü�� ���� �ȼ����� �������� ���� �ְ�
             //direction�� �� �ݴ� ��, ������ �ȼ��� ������ �״ϱ� �����ϸ� ���� ������ ���� �����ϱ� ����ȭ��Ŵ
             float theta=dot(light_dir,normalize(-uLight[i].direction));
             
             float cutoff=cos(radians(uLight[i].cutoffangle));
             if(theta<cutoff)
             {
                continue;
             }                
        }

        //���� ǥ������ ���ϴ� ����
        vec3 surface_dir= (-light_dir);

        //Ambient
        //todo
        //�ؿ� vec3(1.0~)�̰� uMp_Ambient ��ɷ� ��ü�Ǿ����
        vec3 ambient = vec3(1.0f,1.0f,1.0f)* uLight[i].ambient;

        //Diffuse
        vec3 diffuse= vec3(1.0f,1.0f,1.0f)*max(dot(normalize(WorldNormal),light_dir),0.0);  
       

        //Specular
        vec3 reflectDir=reflect(-light_dir,WorldNormal);
        //todo ������ �� uniform ���̴� ������ �����ϼ�
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 302.f);
        
        //todo ��͵� vec3(1.0) uMp_Specular�� ���ټ�
        vec3 specular = vec3(1.0f,1.0f,1.0f) * uLight[i].specular * spec;

        Phong+=(specular+ambient+diffuse)*vec3(UV,0);
    }

    if(uLightColorOn)
    {
        color=vec4(1.0,1.0,1.0,1.0);
        return;
    }
        
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
            color = vec4(Phong,1.0);
        }        
    }    
    else
    {
        color = vec4(Phong, 1.0); // UV ���� ������
    }
}

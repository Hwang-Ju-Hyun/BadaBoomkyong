#version 460

in vec2 UV;
in vec3 WorldPosition;
in vec3 WorldNormal;
in mat3 tbnMat;

out vec4 color;

uniform bool uIsCollider;
uniform bool uHasTexture;
uniform sampler2D uOutTexture;
uniform bool uHurtEffect;
uniform vec3 uCameraPosition;
uniform bool uLightAffect;


// ---- Fog 관련 uniform 추가 ----
uniform vec3  uFogColor;   // 안개 색 (예: vec3(0.9, 0.85, 0.7))
uniform float uFogStart;  // 안개 시작 거리
uniform float uFogEnd;    // 안개 끝나는 거리
uniform bool  uFogOn;

struct Light
{
    int type;
    vec3 position; //월드기준 포지션임
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
uniform bool uLightColorOn;


//=====NORMAL MAPPING=====
//========================

uniform sampler2D uNormalMap;
uniform bool uHasNormalMap;

//========================
//=====NORMAL MAPPING=====



void main()
{    
    vec3 Phong=vec3(0.f,0.f,0.f);
    vec3 PhongTemp=vec3(0.f,0.f,0.f);

    vec3 N;
    if (uHasNormalMap)
    {
        vec3 normalTS = texture(uNormalMap, UV).rgb;        
        normalTS = normalTS * 2.0 - 1.0; // [0,1] → [-1,1]

        //tangent space -> world space

        normalTS = tbnMat * normalTS;                
        N = normalize(normalTS);
    }
    else
    {
        N = normalize(WorldNormal);
    }



    //카메라 방향벡터
    vec3 viewDir=normalize(uCameraPosition-WorldPosition);

    //표면에서 광원까지 
    vec3 light_dir;

    for(int i=0;i<uLightNumber;i++)
    {       
        //POINT TYPE
        if(uLight[i].type==0)
        {
            // 거리 기반 감쇠 (Attenuation)
            //float distance = length(uLight[i].position - WorldPosition);
            //float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
            light_dir = normalize(uLight[i].position-WorldPosition);
            
            // 단순 밝기 계산 (diffuse만 사용)
            //float diffuse = max(dot(N, lightDir), 0.0);

            //Phong += diffuse * attenuation * uLight[i].diffuse;
            //PhongTemp=Phong;
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
             
             //uLight[i].direction 음수화 시킨 이유:
             //light_dir자체가 지금 픽셀에서 조명으로 가고 있고
             //direction은 그 반대 즉, 조명에서 픽셀로 가는중 그니깐 내적하면 완전 엉뚱한 값이 나오니깐 음수화시킴
             float theta=dot(light_dir,normalize(-uLight[i].direction));
             
             float cutoff=cos(radians(uLight[i].cutoffangle));
             if(theta<cutoff)
             {
                continue;
             }                
        }

        //빛이 표면으로 향하는 벡터
        vec3 surface_dir= (-light_dir);

        //Ambient
        //todo
        //밑에 vec3(1.0~)이거 uMp_Ambient 요걸로 대체되어야함
        vec3 ambient = vec3(1.0f,1.0f,1.0f)* uLight[i].ambient;

        //Diffuse
        vec3 diffuse= vec3(1.0f,1.0f,1.0f)*uLight[i].diffuse*max(dot(normalize(N),light_dir),0.0);         


        //Specular
        vec3 reflectDir=reflect(-light_dir,N);
        //todo 마지막 값 uniform 샤이니 값으로 변경하셈
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.f);
          
        //todo 요것도 vec3(1.0) uMp_Specular로 봐꾸셈
        vec3 specular = vec3(1.0f,1.0f,1.0f) * uLight[i].specular * spec;

        
        Phong+=(specular+ambient+diffuse);
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
            if(uLightAffect)
                color = vec4(Phong,1.0)*texColor;
            else
            {
                color = texColor;
                return;
            }               
         }         
    }    
    //else
    //{
    //    color = vec4(UV,0.0,0.0); // UV 색상 디버깅용
    //}


      // ---- Fog 처리 ----
      if(uFogOn)
      {
        float distanceToCamera = length(uCameraPosition - WorldPosition);

        // 선형 Fog factor 계산
        float fogFactor = (uFogEnd - distanceToCamera) / (uFogEnd - uFogStart);
        fogFactor = clamp(fogFactor, 0.0, 1.0);

        // Fog 적용 (안개색과 픽셀색 혼합)
        color.rgb = mix(uFogColor, color.rgb, fogFactor);   
      }    
}
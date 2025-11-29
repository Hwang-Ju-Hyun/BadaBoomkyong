#pragma once
#include "BaseComponent.h"
class CubeMapResource;

class SkyBox :
    public BaseComponent
{
public:
    SkyBox(GameObject* _owner);
    virtual ~SkyBox()override;
private:
    CubeMapResource* m_pCubeMapResource;
public:
    inline CubeMapResource* GetCubeMapResource()const { return m_pCubeMapResource; }
public:
    static constexpr const char* SkyBoxTypeName = "SkyBox";    
    static constexpr const char* SkyBoxName = "SkyBoxName";
    static constexpr const char* SkyBoxFacesPathName = "SkyBoxFacesPath";
    static BaseRTTI* CreateSkyBoxComponent();
    virtual void LoadFromJson(const json& _str) override;
    virtual json SaveToJson(const json& _str)   override;

};


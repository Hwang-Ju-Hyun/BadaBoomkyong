#pragma once
#include "BaseFactory.h"

class PlatformFactory :
    public BaseFactory
{
public:
    PlatformFactory();
    virtual ~PlatformFactory();    
public:
    void ModifyObject();
    virtual GameObject* CreateObject()override;
public:
    static constexpr const char* PlatformFactoryTypeName = "PlatformFactory";
    static constexpr const char* PlatformTypeName = "Platform";
public:
    static size_t g_PlatformID;
};


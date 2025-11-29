#pragma once
#include "Resource.h"

class TextureResource :
    public BaseResource
{
public:
    TextureResource(const std::string& _name);
    virtual ~TextureResource()override;
private:
    int m_iWidth = 0;
    int m_iHeight = 0;
    int m_iNrChannels = 0;
    unsigned int m_iTextureID = 0;
    bool m_bHasAlphaTexture=false;
public:
    inline int GetTextureWidth()const { return m_iWidth; }
    inline int GetTextureHeight()const { return m_iHeight; }
    inline int GetTextureChannels()const { return m_iNrChannels; }
    inline unsigned int GetTextureID()const { return m_iTextureID; }
    inline const bool GetHasAlphaTexture()const { return m_bHasAlphaTexture; }
public:
    virtual void Load(const std::string& _path)override;
    virtual void UnLoad()override;
};


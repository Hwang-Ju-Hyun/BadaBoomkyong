#pragma once
#include "Resource.h"
#include <vector>

class CubeMapResource :
    public BaseResource
{
public:
    CubeMapResource(const std::string& _name);
    virtual ~CubeMapResource()override;
private:
    std::vector<std::string> m_vecFacesCubemap;
public:
    inline const std::vector<std::string>* GetFacesCubeMap() const { return &m_vecFacesCubemap; }
public:
    inline const std::string AddFace(const std::string& _path) { m_vecFacesCubemap.push_back(_path); }
private:
    int m_iWidth = 0;
    int m_iHeight = 0;
    int m_iNrChannels = 0;
    unsigned int m_iTextureID = 0;
    bool m_bHasAlphaTexture = false;
public:
    inline int GetTextureWidth()const { return m_iWidth; }
    inline int GetTextureHeight()const { return m_iHeight; }
    inline int GetTextureChannels()const { return m_iNrChannels; }
    inline unsigned int GetTextureID()const { return m_iTextureID; }
    inline const bool GetHasAlphaTexture()const { return m_bHasAlphaTexture; }
public:
    virtual void Load(const std::string& _path)override {}
    virtual void LoadCubeMap(const std::vector<std::string>& _facesPath)override;
    virtual void UnLoad()override;
};


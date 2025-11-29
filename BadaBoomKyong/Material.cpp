#include "Material.h"
#include <iostream>
#include "TextureResource.h"

Material::Material()
{
}

Material::~Material()
{		
}

bool Material::GetHasAlphaChannel()const
{
    bool channels = false;
    if (m_pDiffuseMap)
    {
        channels = m_pDiffuseMap->GetHasAlphaTexture();
    }    
    if (!channels)
        return false;
    return true;
}

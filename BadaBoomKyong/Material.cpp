#include "Material.h"
#include <iostream>
#include "TextureResource.h"

Material::Material()
{
}

Material::~Material()
{	
	if (m_pDiffuseMap)
	{
		delete m_pDiffuseMap;
		m_pDiffuseMap = nullptr;
	}	
}

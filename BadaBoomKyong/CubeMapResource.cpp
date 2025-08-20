#include "CubeMapResource.h"
#include "stb_image.h"
#include <GL/glew.h>
#include <cassert>
#include <iostream>

CubeMapResource::CubeMapResource(const std::string& _name)
	:BaseResource(_name)
{
	SetResourceName("CubeMap");
}
 
CubeMapResource::~CubeMapResource()
{
}

void CubeMapResource::LoadCubeMap(const std::vector<std::string>& _facesPath)
{

	glGenTextures(1, &m_iTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		m_cData = stbi_load(_facesPath[i].c_str(), &m_iWidth, &m_iHeight, &m_iNrChannels, 0);
		if (m_cData)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				m_iWidth,
				m_iHeight,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				m_cData
			);
			stbi_image_free(m_cData);
		}
		else
		{
			std::cout << "Failed to load texture: " << _facesPath[i] << std::endl;
			stbi_image_free(m_cData);
		}
	}
		
	m_bHasAlphaTexture = false;

	SetResourcePath(_facesPath[0]);
}

void CubeMapResource::UnLoad()
{
}

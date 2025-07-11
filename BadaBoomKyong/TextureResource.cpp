#include "TextureResource.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <cassert>
#include <iostream>
TextureResource::TextureResource(const std::string& _name)
    :BaseResource(_name)
{
}

TextureResource::~TextureResource()
{
    UnLoad();
}

#include <iostream>
void TextureResource::Load(const std::string& _path)
{
    //	�̹��� ������ ���α׷� �޸𸮷� �ҷ���
    std::cout << "Loading texture: " << _path << std::endl;
    
    m_cData = stbi_load(_path.c_str(), &m_iWidth, &m_iHeight, &m_iNrChannels, 0);
    //assert(m_cData != nullptr);
    if (!m_cData)
    {
        std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }
    glGenTextures(1, &m_iTextureID);    //�ؽ�ó ID ���� (�ؽ�ó �ϳ� ����ٰ� ���� ��)    
    glBindTexture(GL_TEXTURE_2D, m_iTextureID);//Ȱ��ȭ
    
    // �ؽ�ó wrapping/filtering �ɼ� ����(���� ���ε��� �ؽ�ó ��ü�� ����)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    if (m_iNrChannels == 1)
        format = GL_RED;
    else if (m_iNrChannels == 3)
        format = GL_RGB;
    else if (m_iNrChannels == 4)
        format = GL_RGBA;
    else {
        std::cerr << "Unsupported channel count: " << m_iNrChannels << std::endl;
        stbi_image_free(m_cData);
        return;
    }
    //�̹��� �����͸� GPU �ؽ�ó�� ���ε�
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_iWidth, m_iHeight, 0, format, GL_UNSIGNED_BYTE, m_cData);
    
    stbi_image_free(m_cData);
    SetResourcePath(_path);
}

void TextureResource::UnLoad()
{    
    glDeleteTextures(1, &m_iTextureID);
    m_iTextureID = 0;
    m_iWidth = 0;
    m_iHeight = 0;
    m_iNrChannels = 0;
    m_cData = nullptr;
}
#include "TextureResource.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <cassert>

TextureResource::TextureResource(const std::string& _name)
    :BaseResource(_name)
{
}

TextureResource::~TextureResource()
{
}

void TextureResource::Load(const std::string& _path)
{
    //	�̹��� ������ ���α׷� �޸𸮷� �ҷ���
    m_cData = stbi_load(_path.c_str(), &m_iWidth, &m_iHeight, &m_iNrChannels, 0);
    assert(m_cData != nullptr);

    glGenTextures(1, &m_iTextureID);    //�ؽ�ó ID ���� (�ؽ�ó �ϳ� ����ٰ� ���� ��)    
    glBindTexture(GL_TEXTURE_2D, m_iTextureID);//Ȱ��ȭ

    // �ؽ�ó wrapping/filtering �ɼ� ����(���� ���ε��� �ؽ�ó ��ü�� ����)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //�̹��� �����͸� GPU �ؽ�ó�� ���ε�
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iWidth, m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_cData);
    
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
}

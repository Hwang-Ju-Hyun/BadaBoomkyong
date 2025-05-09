#include "FrameBuffer.h"
#include <GL/glew.h>
#include <iostream>

FrameBuffer::FrameBuffer(float _width, float _height)
	:m_fWidth(_width),
	m_fHeight(_height)
{
	glGenFramebuffers(1, &m_uFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);

	glGenTextures(1, &m_uTexture);
	glBindTexture(GL_TEXTURE_2D, m_uTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_fWidth, m_fHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//프레임버퍼(FBO)에 텍스처를 붙이는 함수
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uTexture, 0);

	// 렌더 버퍼 생성
	glGenRenderbuffers(1, &m_uRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_uRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fWidth, m_fHeight);  // 메모리 할당
	// 프레임버퍼에 그릴 때 렌더 버퍼의 정보(depth, stencil)를 사용
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_uFBO);
	glDeleteTextures(1, &m_uTexture);
	glDeleteRenderbuffers(1, &m_uRBO);
}

unsigned int FrameBuffer::getFrameTexture()
{
	return m_uTexture;
}

void FrameBuffer::RescaleFrameBuffer(float width, float height)
{
}

void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);
}

void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

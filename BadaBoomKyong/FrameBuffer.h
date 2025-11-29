#pragma once
class FrameBuffer
{
public:
	FrameBuffer(float _width, float _height);
	~FrameBuffer();
public:
	unsigned int getFrameTexture();
	void RescaleFrameBuffer(float width, float height);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_uFBO;
	unsigned int m_uTexture;
	unsigned int m_uRBO;
private:
	float m_fWidth=0.f;
	float m_fHeight = 0.f;
};


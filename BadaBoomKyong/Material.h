#pragma once

class TextureResource;

class Material
{
public:
	Material();
	~Material();
private:
	TextureResource* m_pDiffuseMap = nullptr;
public:
	inline bool HasTexture()const { return m_pDiffuseMap!=nullptr; }
	inline TextureResource* GetTexture()const { return m_pDiffuseMap; }
	inline void SetTexture(TextureResource* _tex) { m_pDiffuseMap = _tex; }
};
#pragma once
#include <glm.hpp>

class TextureResource;

class Material
{
public:
	Material();
	~Material();
private:
	TextureResource* m_pDiffuseMap = nullptr;
	//light
	glm::vec3 m_vAmbient;  // 주변광 반사율
	glm::vec3 m_vDiffuse;  // 난반사 반사율
	glm::vec3 m_vSpecular; // 정반사 반사율
	float m_fShininess = 102.0f;           // 반짝임 정도
public:
	inline bool HasTexture()const { return m_pDiffuseMap!=nullptr; }
	inline TextureResource* GetTexture()const { return m_pDiffuseMap; }
	inline void SetTexture(TextureResource* _tex) { m_pDiffuseMap = _tex; }
	bool GetHasAlphaChannel()const;
public:
	inline void SetAmbient(const glm::vec3 _amb) { m_vAmbient = _amb; }
	inline void SetDiffuse(const glm::vec3 _diff) { m_vDiffuse = _diff; }
	inline void SetSpecular(const glm::vec3 _spc) { m_vSpecular = _spc; }
	inline void SetShininess(float _shiny) { m_fShininess = _shiny; }

	inline void AddAmbient(const glm::vec3 _amb) { m_vAmbient += _amb; }
	inline void AddDiffuse(const glm::vec3 _diff) { m_vDiffuse += _diff; }
	inline void AddSpecular(const glm::vec3 _spc) { m_vSpecular += _spc; }
	inline void AddShininess(float _shiny) { m_fShininess += _shiny; }

	glm::vec3 GetAmbient()const { return m_vAmbient; }
	glm::vec3 GetDiffuse()const { return m_vDiffuse; }
	glm::vec3 GetSpecular()const { return m_vSpecular; }
	float GetShininess()const { return m_fShininess; }
};
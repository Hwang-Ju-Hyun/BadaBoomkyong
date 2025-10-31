#pragma once
#include <glm.hpp>

class GameObject;


struct RayCastHit
{
	bool m_bIsHit = false;
	glm::vec3 m_vPoint;
	float m_fDistance;
	GameObject* m_pHitGameObject;	
};

struct Ray
{
	glm::vec3 m_vPosition;
	glm::vec3 m_vDirection;		
};
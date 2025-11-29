#pragma once
#include "BehaviorTreeNode.h"
#include <glm.hpp>

class Player;
class Boss;
class Transform;
class RigidBody;
class Camera;

enum class ConeAttackState
{	
	GO,
	ATTACKING,
	BACK
};

class ConeAttack :
    public BTNode
{
public:
	ConeAttack(Boss* _boss);
	virtual ~ConeAttack()override;
	virtual BTNodeState Enter(BlackBoard& _bb);
	virtual BTNodeState Update(BlackBoard& _bb);
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort();
private:
	ConeAttackState m_eState;
	Boss* m_pBoss;
	Player* m_pPlayer;
	Transform* m_pBossTransform;
	Transform* m_pPlayerTransform;
	RigidBody* m_pBossRigidBody;
	glm::vec3 m_vPlayer_pos;
	glm::vec3 m_vBoss_pos;
	glm::vec3 m_vConeCamPos;
	Camera* m_pCam;
public:
	float m_fDisappear_AccTime = 0.f;
	float m_fDisappear_MaxTime = 3.f;

	float m_fAppear_AccTime = 0.f;
	float m_fAppear_MaxTime = 5.f;

	bool m_bFlag = false;
	bool m_bIsTeleported = false;
	bool m_bConeAttackReady = false;
	bool m_bConeAttackNotDone = true;
	
};


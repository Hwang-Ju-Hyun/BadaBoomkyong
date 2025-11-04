#pragma once
#include "BehaviorTreeNode.h"

class Boss;
class Transform;
class Player;

class TeleportAttack :
    public BTNode
{
public:
	TeleportAttack(Boss* _boss);
	virtual BTNodeState Enter(BlackBoard& _bb)override;
	virtual BTNodeState Update(BlackBoard& _bb)override;
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort();
public:
	Boss* m_pBoss;
	Transform* m_pBossTransform;
	Player* m_pPlayer;
	Transform* m_pPlayerTransform;
	float m_fDisappear_AccTime = 0.f;
	float m_fDisappear_MaxTime = 3.f;

	float m_fAppear_AccTime = 0.f;
	float m_fAppear_MaxTime = 5.f;

	bool m_bFlag = false;
	bool m_bIsTeleported = false;
};


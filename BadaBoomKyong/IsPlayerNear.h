#pragma once
#include "BehaviorTreeNode.h"
#include <glm.hpp>

class Player;
class Boss;

class IsPlayerNear :
	public BTNode
{
public:
	IsPlayerNear(Boss* _boss);
	virtual ~IsPlayerNear()override;
	virtual BTNodeState Enter(BlackBoard& _bb);
	virtual BTNodeState Update(BlackBoard& _bb);
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort();
private:
	Boss* m_pBoss;
	Player* m_pPlayer;
	glm::vec3 m_vPlayer_pos;
	glm::vec3 m_vBoss_pos;
};


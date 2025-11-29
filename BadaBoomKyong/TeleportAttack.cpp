#include "TeleportAttack.h"
#include "Boss.h"
#include "BlackBoard.h"
#include "Transform.h"
#include "Animator.h"
#include <iostream>

TeleportAttack::TeleportAttack(Boss* _boss)
{
}

TeleportAttack::~TeleportAttack()
{
}

BTNodeState TeleportAttack::Enter(BlackBoard& _bb)
{
	m_pBoss = _bb.GetBoss();
	m_pBossTransform = _bb.GetBossTransform();
	m_pPlayer = _bb.GetPlayer();
	m_pPlayerTransform = _bb.GetPlayerTransform();

	if (m_pBoss->GetCurrentHP() > 11)
	{
		return BTNodeState::FAILURE;
	}
    if(!m_pBoss->GetIsGround())
        return BTNodeState::FAILURE;    
	m_pBoss->SetCurrentAnimState(MonsterAnimState::DISAPPEAR);
	return BTNodeState::RUNNING;
}
#include "TimeManager.h"
BTNodeState TeleportAttack::Update(BlackBoard& _bb)
{		
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    m_fDisappear_AccTime += dt;

    Animator* anim = m_pBoss->GetAnimator();
    if (!anim) return BTNodeState::FAILURE;

    //사라지는 중
    if (!m_bFlag)
    {
        // 사라짐 애니 끝났다면
        if (anim->GetAnimation()->m_bLoopCount >= 1 &&
            m_pBoss->GetCurrentState() == MonsterAnimState::DISAPPEAR)
        {
            m_pBoss->TelePort({ -10000.f, -10000.f, -10000.f });
            m_bFlag = true; // 다음 단계로
            std::cout << "[TeleportAttack] Boss disappeared\n";
        }
        return BTNodeState::RUNNING;
    }

    // 사라진 상태  플레이어 위치로 이동
    if (m_bFlag && !m_bIsTeleported)
    {
        glm::vec3 player_upper = {
            m_pPlayerTransform->GetPosition().x,
            m_pPlayerTransform->GetPosition().y + 100.f,
            m_pPlayerTransform->GetPosition().z
        };

        m_pBoss->TelePort(player_upper);
        m_pBoss->SetCurrentAnimState(MonsterAnimState::APPEAR);
        m_pBoss->SetTargetPos(m_pPlayerTransform->GetPosition());
        m_bIsTeleported = true;
        std::cout << "[TeleportAttack] Boss teleported to player\n";
        return BTNodeState::RUNNING;
    }

    // 등장 완료
    if (m_bIsTeleported)
    {
        if (anim->GetAnimation()->m_bLoopCount >= 1 &&
            m_pBoss->GetCurrentState() == MonsterAnimState::APPEAR)
        {
            m_bFlag = false;
            m_bIsTeleported = false;
            std::cout << "[TeleportAttack] Appear done\n";            
            return BTNodeState::SUCCESS;
        }
    }

    return BTNodeState::RUNNING;

}

void TeleportAttack::Exit(BlackBoard& _bb)
{
}

void TeleportAttack::Abort()
{
}

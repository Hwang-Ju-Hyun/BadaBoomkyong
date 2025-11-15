#include "ConeAttack.h"
#include "Boss.h"
#include "BlackBoard.h"
#include "Animator.h"
#include "Player.h"
#include "Transform.h"
#include "TimeManager.h"
#include "RigidBody.h"
#include "ConeRange.h"

ConeAttack::ConeAttack(Boss* _boss)
    :m_pBoss(_boss)
{
}

BTNodeState ConeAttack::Enter(BlackBoard& _bb)
{
	m_pBoss = _bb.GetBoss();
	m_pPlayer = _bb.GetPlayer();
    m_pBossRigidBody = _bb.GetBossRigidBody();
    m_pPlayerTransform = _bb.GetPlayerTransform();
	m_vPlayer_pos = m_pPlayer->GetPosition();
	m_vBoss_pos = m_pBoss->GetPosition();
	
	//glm::vec3 target_pos = glm::vec3{ -300,1600,-800 };
	//
	//m_pBoss->TelePort(target_pos);
	
	m_pBoss->SetCurrentAnimState(MonsterAnimState::DISAPPEAR);

	return BTNodeState::RUNNING;
}

BTNodeState ConeAttack::Update(BlackBoard& _bb)
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    m_fDisappear_AccTime += dt;

    Animator* anim = m_pBoss->GetAnimator();
    if (!anim) 
        return BTNodeState::FAILURE;

    switch (m_eState)
    {
    case ConeAttackState::GO:
    {
        //사라지는 중
        if (!m_bFlag)
        {
            // 사라짐 애니 끝났다면
            if (anim->GetAnimation()->m_bLoopCount >= 1 &&
                m_pBoss->GetCurrentState() == MonsterAnimState::DISAPPEAR)
            {
                m_pBoss->TelePort({ -10000.f, -10000.f, -10000.f });
                m_bFlag = true; // 다음 단계로            
            }
            return BTNodeState::RUNNING;
        }

        // 사라진 상태  플레이어 위치로 이동
        if (m_bFlag && !m_bIsTeleported )
        {
            glm::vec3 target_pos = { -100,1800,-800 };
            m_pBoss->GetRigidBody()->SetIsKinematic(true);
            m_pBoss->TelePort(target_pos);
            m_pBoss->SetCurrentAnimState(MonsterAnimState::APPEAR);
            m_pBoss->SetTargetPos(m_pPlayerTransform->GetPosition());
            m_bIsTeleported = true;
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
                m_pBoss->SpawnPawn();
                m_eState = ConeAttackState::ATTACKING;
            }
            return BTNodeState::RUNNING;
        }
    }
        break;
    case ConeAttackState::ATTACKING:
    {                            
        bool flag = false;
        for (auto iter : m_pBoss->GetConeVec())
        {
            if (iter->GetActive())
            {
                flag = true;
                return BTNodeState::RUNNING;
            }
        }
        if (!flag)
        {
            m_pBoss->SetCurrentAnimState(MonsterAnimState::DISAPPEAR);
            if (m_pBoss->GetAnimator()->GetAnimation()->m_bLoopCount >= 1 && m_pBoss->GetCurrentState() == MonsterAnimState::DISAPPEAR)
            {
                glm::vec3 player_pos_upper = {
                    m_pPlayerTransform->GetPosition().x,
                    m_pPlayerTransform->GetPosition().y + 100.f,
                    m_pPlayerTransform->GetPosition().z
                };
                glm::vec3 target_pos = player_pos_upper;
                m_pBoss->TelePort(target_pos);
                m_pBoss->GetRigidBody()->SetIsKinematic(false);
                m_pBoss->SetTargetPos(m_pPlayerTransform->GetPosition());
                m_eState = ConeAttackState::BACK;
            }            
        }
        return BTNodeState::RUNNING;
    }
        break;
    case ConeAttackState::BACK:
    {   
        m_pBoss->SetCurrentAnimState(MonsterAnimState::APPEAR);
        if (m_pBoss->GetCurrentState() == MonsterAnimState::APPEAR && m_pBoss->GetAnimator()->GetAnimation()->m_bLoopCount >= 1)
        {
            return BTNodeState::SUCCESS;
        }                        
        return BTNodeState::RUNNING;
    }
        break;
    default:
        break;
    }           
}


void ConeAttack::Exit(BlackBoard& _bb)
{
    Boss* b = _bb.GetBoss();
    std::vector<Bullet*>& vec = b->GetConeVec();
    vec.clear();
    m_eState = ConeAttackState::GO;
    //m_pBoss->GetRigidBody()->SetIsKinematic(false);
}

void ConeAttack::Abort()
{
}

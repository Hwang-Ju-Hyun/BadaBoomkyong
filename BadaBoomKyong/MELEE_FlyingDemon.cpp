#include "MELEE_FlyingDemon.h"
#include "AI.h"
#include "FlyingDemon.h"
#include <cassert>
#include "RigidBody.h"
#include <iostream>
#include "Transform.h"
#include "header.h"
#include "Animator.h"
#include "TimeManager.h"
#include "Player.h"
#include "MathUtil.h"
#include "TimeManager.h"
#include "CollisionManager.h"

void MELEE_FlyingDemon::Init(Monster* _mon)
{
	m_pFlyingDemon = dynamic_cast<FlyingDemon*>(_mon);
	assert(m_pFlyingDemon != nullptr);

	m_pRigidBody = dynamic_cast<RigidBody*>(m_pFlyingDemon->GetOwner()->FindComponent<RigidBody>());
	assert(m_pRigidBody != nullptr);

	m_pTransform = dynamic_cast<Transform*>(m_pFlyingDemon->GetOwner()->FindComponent<Transform>());
	assert(m_pTransform != nullptr);

	m_pPlayer= dynamic_cast<Player*>(_mon->GetPlayer());	

	m_pAnimator = dynamic_cast<Animator*>(m_pFlyingDemon->GetOwner()->FindComponent<Animator>());
	assert(m_pAnimator != nullptr);

	m_fMeleeAtkCoolTime = _mon->GetMeleeAtkCoolTime();
}

void MELEE_FlyingDemon::DoMeleeBehaviour(Monster* _mon)
{	            
    if (m_pPlayer == nullptr)
        return;
    float dt = TimeManager::GetInstance()->GetDeltaTime();

    m_vPosition = m_pTransform->GetPosition();
    Transform* player_trs = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>());
    glm::vec3 player_pos = player_trs->GetPosition();

    if (m_bCanTakeOff)
    {
        // TakeOff 이동
        glm::vec3 takeOffTarget = { m_vPosition.x, m_vPosition.y + 400.f, m_vPosition.z }; // 예시: 위쪽으로 이동
        float takeOffSpeed = 500.f;
        glm::vec3 takeOffDir = glm::normalize(takeOffTarget - m_vPosition);
        m_pTransform->AddPosition(takeOffDir * takeOffSpeed * dt);
    
        m_fTakeOffAccTime += dt;
        if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1 && m_pFlyingDemon->GetCurrentState() == MonsterAnimState::TAKE_OFF)
        {
            m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::FLYING);
        }
        if (m_fTakeOffAccTime >= m_fMaxTakingOffTime)
        {
            // TakeOff 종료, Trace 상태 복귀
            m_bDiveAttacking = false;
            m_bCanTakeOff = false;
            m_fTakeOffAccTime = 0.f;
            m_pFlyingDemon->GetAI()->ChangeState(MONSTER_STATE::TRACE_STATE);            
        }
        return;
    }

    // === Dive Attack 준비 ===
    if (!m_bDiveAttacking)
    {
        target_pos = player_pos;                        // 공격 대상 위치 기록
        glm::vec3 dir = glm::normalize(target_pos - m_vPosition);

        m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::DIVE_START);
        std::cout << m_pFlyingDemon->GetCurrentAnimState() << std::endl;
        // DIVE_START 애니메이션 1회 완료 시 Dive 상태 전환
        if (m_pFlyingDemon->GetAnimator()->GetAnimation()->m_bLoopCount >= 1 &&
            m_pFlyingDemon->GetCurrentState() == MonsterAnimState::DIVE_START)
        {
            m_bDiveAttacking = true;
        }
    }
    else // === Dive Attack 진행 중 ===
    {
        glm::vec3 dir = glm::normalize(target_pos - m_vPosition);
       

        // 공격 범위 도달 여부 (Magic Number 제거)
        float attackThresholdX = 10.5f; // m 단위
        float attackThresholdY = 100.5f;

        if (std::fabs(m_vPosition.x - target_pos.x) < attackThresholdX &&
            std::fabs(m_vPosition.y - target_pos.y) < attackThresholdY)
        {
            // 공격 애니메이션
            if (m_pFlyingDemon->GetCurrentState() != MonsterAnimState::NORMAL_ATTACK)
                m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::NORMAL_ATTACK);

            m_fMeleeCoolTimeAcc += dt;

            // 특정 프레임에서 실제 공격
            if (m_pFlyingDemon->GetAnimator()->GetCurrentFrameIndex() == 4)
                m_pFlyingDemon->MeleeAttack();

            // 공격 애니메이션 끝나면 TakeOff
            if (m_pFlyingDemon->GetAnimator()->GetAnimation()->m_bLoopCount >= 1&&m_pFlyingDemon->GetCurrentState() == MonsterAnimState::NORMAL_ATTACK)
            {
                m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::TAKE_OFF);               
                m_bCanTakeOff = true;               
            }
        }
        else
        {
            // Dive 중 이동
            if (m_pFlyingDemon->GetCurrentState() != MonsterAnimState::DIVING)
                m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::DIVING);

            float diveSpeed = 500.f;
            m_pTransform->AddPosition(dir * diveSpeed * dt);
        }
    }

    // Collision 체크 (필요하면 추가)
    

    // 디버그
    //std::cout << "Melee State: " << m_pTransform->GetPosition().x << "," << m_pTransform->GetPosition().y << std::endl;

}

MELEE_FlyingDemon::~MELEE_FlyingDemon()
{
}

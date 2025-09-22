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
    float dt = TimeManager::GetInstance()->GetDeltaTime();

    m_vPosition = m_pTransform->GetPosition();
    Transform* player_trs = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent<Transform>());
    glm::vec3 player_pos = player_trs->GetPosition();

    if (m_bCanTakeOff)
    {
        // TakeOff �̵�
        glm::vec3 takeOffTarget = { m_vPosition.x, m_vPosition.y + 400.f, m_vPosition.z }; // ����: �������� �̵�
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
            // TakeOff ����, Trace ���� ����
            m_bDiveAttacking = false;
            m_bCanTakeOff = false;
            m_fTakeOffAccTime = 0.f;
            m_pFlyingDemon->GetAI()->ChangeState(MONSTER_STATE::TRACE_STATE);            
        }
        return;
    }

    // === Dive Attack �غ� ===
    if (!m_bDiveAttacking)
    {
        target_pos = player_pos;                        // ���� ��� ��ġ ���
        glm::vec3 dir = glm::normalize(target_pos - m_vPosition);

        m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::DIVE_START);
        std::cout << m_pFlyingDemon->GetCurrentAnimState() << std::endl;
        // DIVE_START �ִϸ��̼� 1ȸ �Ϸ� �� Dive ���� ��ȯ
        if (m_pFlyingDemon->GetAnimator()->GetAnimation()->m_bLoopCount >= 1 &&
            m_pFlyingDemon->GetCurrentState() == MonsterAnimState::DIVE_START)
        {
            m_bDiveAttacking = true;
        }
    }
    else // === Dive Attack ���� �� ===
    {
        glm::vec3 dir = glm::normalize(target_pos - m_vPosition);
       

        // ���� ���� ���� ���� (Magic Number ����)
        float attackThresholdX = 10.5f; // m ����
        float attackThresholdY = 100.5f;

        if (std::fabs(m_vPosition.x - target_pos.x) < attackThresholdX &&
            std::fabs(m_vPosition.y - target_pos.y) < attackThresholdY)
        {
            // ���� �ִϸ��̼�
            if (m_pFlyingDemon->GetCurrentState() != MonsterAnimState::NORMAL_ATTACK)
                m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::NORMAL_ATTACK);

            m_fMeleeCoolTimeAcc += dt;

            // Ư�� �����ӿ��� ���� ����
            if (m_pFlyingDemon->GetAnimator()->GetCurrentFrameIndex() == 4)
                m_pFlyingDemon->MeleeAttack();

            // ���� �ִϸ��̼� ������ TakeOff
            if (m_pFlyingDemon->GetAnimator()->GetAnimation()->m_bLoopCount >= 1&&m_pFlyingDemon->GetCurrentState() == MonsterAnimState::NORMAL_ATTACK)
            {
                m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::TAKE_OFF);               
                m_bCanTakeOff = true;               
            }
        }
        else
        {
            // Dive �� �̵�
            if (m_pFlyingDemon->GetCurrentState() != MonsterAnimState::DIVING)
                m_pFlyingDemon->SetAnimCurrentState(MonsterAnimState::DIVING);

            float diveSpeed = 500.f;
            m_pTransform->AddPosition(dir * diveSpeed * dt);
        }
    }

    // Collision üũ (�ʿ��ϸ� �߰�)
    

    // �����
    //std::cout << "Melee State: " << m_pTransform->GetPosition().x << "," << m_pTransform->GetPosition().y << std::endl;

}

MELEE_FlyingDemon::~MELEE_FlyingDemon()
{
}

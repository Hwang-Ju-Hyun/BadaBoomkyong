#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "Monster.h"
#include "EventManager.h"

template<typename T>
class AnimNormalAttackState_3 : public AnimIState<T>
{
public:
    AnimNormalAttackState_3() {}
    virtual ~AnimNormalAttackState_3() override {}
    PlayerMelee* m_pMelee;
public:
    virtual void Enter(T* _owner) override
    {
        if constexpr (std::is_same<T, Player>::value)
        {
            m_pMelee = dynamic_cast<PlayerMelee*>(_owner->GetMelee());
            if (m_pMelee)
            {
                _owner->m_bCanMeleeAttack = true;
                EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
                //m_pMelee->SetLifeTime(2.5f);
                _owner->GetAnimator()->ChangeAnimation("ComboAtk_3");
            }
        }
    }

    virtual void Update(T* _owner) override
    {
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case PlayerAnimState::IDLE:
                machine->ChangeAnimState(PlayerAnimState::IDLE);
                break;
            case PlayerAnimState::HURT:
                machine->ChangeAnimState(PlayerAnimState::HURT);
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override 
    {
        if constexpr (std::is_same<T, Player>::value)
        {
            m_pMelee = dynamic_cast<PlayerMelee*>(_owner->GetMelee());
            if (m_pMelee)
            {
                EventManager::GetInstance()->SetActiveFalse(m_pMelee->GetOwner());
            }
        }
        std::cout << "combo3 exit" << std::endl;
    }
};

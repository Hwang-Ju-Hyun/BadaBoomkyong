#pragma once
#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "Monster.h"
#include "EventManager.h"

template<typename T>
class AnimNormalAttackState_2 : public AnimIState<T>
{
public:
    AnimNormalAttackState_2() {}
    virtual ~AnimNormalAttackState_2() override {}
    PlayerMelee* m_pMelee;
public:
    virtual void Enter(T* _owner) override
    {        
        if constexpr (std::is_same<T, Player>::value)
        {
            m_pMelee= dynamic_cast<PlayerMelee*>(_owner->GetMelee());
            if (m_pMelee)
            {
                _owner->m_bCanMeleeAttack = true;
                EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
                _owner->GetAnimator()->ChangeAnimation("ComboAtk_2");
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
            case PlayerAnimState::COMBO_ATTACK_3:
                machine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_3);
                break;
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
        std::cout << "combo2 exit" << std::endl;
    }
};

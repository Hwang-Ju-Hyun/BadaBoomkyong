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
        _owner->GetAnimator()->ChangeAnimation("ComboAtk_3");
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
            case PlayerAnimState::TOSPRINT:
                machine->ChangeAnimState(PlayerAnimState::TOSPRINT);
                break;
            case PlayerAnimState::SPRINTING:
                machine->ChangeAnimState(PlayerAnimState::SPRINTING);
                break;
            case PlayerAnimState::JUMP:
                machine->ChangeAnimState(PlayerAnimState::JUMP);
                break;
            case PlayerAnimState::FALL:
                machine->ChangeAnimState(PlayerAnimState::FALL);
                break;
            case PlayerAnimState::DASH:
                machine->ChangeAnimState(PlayerAnimState::DASH);
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
                m_pMelee->SetDamage(1);
                EventManager::GetInstance()->SetActiveFalse(m_pMelee->GetOwner());
            }
        }        
    }
};

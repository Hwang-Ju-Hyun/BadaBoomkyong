#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "AudioManager.h"


template<typename T>
class AnimDashState : public AnimIState<T>
{
public:
    AnimDashState() {}
    virtual ~AnimDashState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Dash");        
        AudioManager::GetInstance()->PlaySound("dash", 1.0f);
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
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};

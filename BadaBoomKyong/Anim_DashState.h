#pragma once
#include "Anim_IState.h"
#include "Anim_HurtState.h"
#include "AudioManager.h"
template<typename T>
class AnimIdleState;  // Forward declaration
template<typename T>
class AnimDeathState;  // Forward declaration

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
        if constexpr (std::is_same<T, Player>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case PlayerAnimState::IDLE:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimIdleState<T>());
                break;
            case PlayerAnimState::HURT:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimHurtState<T>());
                break;
            case PlayerAnimState::TOSPRINT:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimToSprintState<T>());
                break;
            case PlayerAnimState::SPRINTING:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimSprintingState<T>());
                break;
            case PlayerAnimState::DEATH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDeathState<T>());
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};

#pragma once
#include "Anim_IState.h"
#include "Anim_SprintingState.h"

template<typename T>
class AnimIdleState;  // Forward declaration
template<typename T>
class AnimDeathState;  // Forward declaration
template<typename T>
class AnimDashState;  // Forward declaration

template<typename T>
class AnimToSprintState : public AnimIState<T>
{
public:
    AnimToSprintState() {}
    virtual ~AnimToSprintState() override {}
public:
    virtual void Enter(T* _owner) override 
    {
        _owner->GetAnimator()->ChangeAnimation("ToSprint");
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
            case PlayerAnimState::SPRINTING:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimSprintingState<T>());
                break;
            case  PlayerAnimState::RUN_ATTACK:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimSprintAttackState<T>());
                break;
            case PlayerAnimState::DASH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDashState<T>());
                break;
            case PlayerAnimState::DEATH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDeathState<T>());
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};

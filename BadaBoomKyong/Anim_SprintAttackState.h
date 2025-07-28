#pragma once
#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimIdleState;  // Forward declaration

template<typename T>
class AnimDeathState;  // Forward declaration

template<typename T>
class AnimSprintingState;

template<typename T>
class AnimSprintAttackState : public AnimIState<T>
{
public:
    AnimSprintAttackState() {}
    virtual ~AnimSprintAttackState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("SprintAttack");
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
            case PlayerAnimState::JUMP:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimJumpState<T>());
                break;
            case PlayerAnimState::FALL:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimFallState<T>());
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

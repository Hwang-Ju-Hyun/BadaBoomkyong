#pragma once
#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimIdleState;  // Forward declaration

template<typename T>
class AnimJumpState;  // Forward declaration

template<typename T>
class AnimFallState;  // Forward declaration

template<typename T>
class AnimDeathState;  // Forward declaration

template<typename T>
class AnimJumpAttackState : public AnimIState<T>
{
public:
    AnimJumpAttackState() {}
    virtual ~AnimJumpAttackState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("JumpAttack");
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
            case PlayerAnimState::DEATH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDeathState<T>());
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};

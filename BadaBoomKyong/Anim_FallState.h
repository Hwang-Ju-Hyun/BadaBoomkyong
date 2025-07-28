#pragma once
#include "Anim_IState.h"
#include "Anim_JumpAttackState.h"

template<typename T>
class AnimIdleState;  // Forward declaration
template<typename T>
class AnimDeathState;

template<typename T>
class AnimFallState : public AnimIState<T>
{
public:
    AnimFallState() {}
    virtual ~AnimFallState() override {}
public:
    virtual void Enter(T* _owner) override 
    {
        _owner->GetAnimator()->ChangeAnimation("Fall");
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
            case PlayerAnimState::JUMP_ATTACK:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimJumpAttackState<T>());
                break;
            case PlayerAnimState::DEATH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDeathState<T>());
                break;
            }           
        }
    }

    virtual void Exit(T* _owner) override {}
};

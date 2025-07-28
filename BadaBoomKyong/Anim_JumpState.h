#pragma once
#include "Anim_IState.h"
#include "Anim_JumpAttackState.h"

template<typename T>
class AnimFallState;  // Forward declaration

template<typename T>
class AnimDeathState;

template<typename T>
class AnimJumpState : public AnimIState<T>
{
public:
    AnimJumpState() {}
    virtual ~AnimJumpState() override {}
public:
    virtual void Enter(T* _owner) override 
    {
        _owner->GetAnimator()->ChangeAnimation("Jump");
    }

    virtual void Update(T* _owner) override 
    {
        if constexpr (std::is_same<T, Player>::value) 
        {
            switch (_owner->GetCurrentState()) 
            {
            case PlayerAnimState::FALL:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimFallState<T>());
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

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
        AnimStateMachine<Player>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value) 
        {
            switch (_owner->GetCurrentState()) 
            {
            case PlayerAnimState::FALL:
                machine->ChangeAnimState(PlayerAnimState::FALL);
                break;
            case PlayerAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(PlayerAnimState::JUMP_ATTACK);
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};

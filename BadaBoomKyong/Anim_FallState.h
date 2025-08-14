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
        AnimStateMachine<Player>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value) 
        {
            switch (_owner->GetCurrentState())
            {
            case PlayerAnimState::IDLE:
                machine->ChangeAnimState(int(PlayerAnimState::IDLE));
                break;
            case PlayerAnimState::TOSPRINT:
                machine->ChangeAnimState(int(PlayerAnimState::TOSPRINT));
                break;
            case PlayerAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(int(PlayerAnimState::JUMP_ATTACK));
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(int(PlayerAnimState::DEATH));
                break;
            }           
        }
    }

    virtual void Exit(T* _owner) override {}
};

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
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
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
            case PlayerAnimState::HURT:
                machine->ChangeAnimState(PlayerAnimState::HURT);
                break;
            case PlayerAnimState::DASH:
                machine->ChangeAnimState(PlayerAnimState::DASH);
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
        else if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::FALL:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::FALL));
                break;
            case MonsterAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::JUMP_ATTACK));
                break;
            case MonsterAnimState::HURT:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::HURT));
                break;
            case MonsterAnimState::DASH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DASH));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};

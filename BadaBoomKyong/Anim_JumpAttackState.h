#pragma once
#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "Monster.h"

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
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value)
        {            
            switch (_owner->GetCurrentState())
            {
            case PlayerAnimState::IDLE:
                machine->ChangeAnimState(PlayerAnimState::IDLE);
                break;
            case PlayerAnimState::JUMP:
                machine->ChangeAnimState(PlayerAnimState::JUMP);
                break;
            case PlayerAnimState::TOSPRINT:
                machine->ChangeAnimState(PlayerAnimState::TOSPRINT);
                break;
            case PlayerAnimState::SPRINTING:
                machine->ChangeAnimState(PlayerAnimState::SPRINTING);
                break;
            case PlayerAnimState::FALL:
                machine->ChangeAnimState(PlayerAnimState::FALL);
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
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::JUMP:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::JUMP));
                break;
            case MonsterAnimState::FALL:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::FALL));
                break;
            case MonsterAnimState::WALK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::WALK));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
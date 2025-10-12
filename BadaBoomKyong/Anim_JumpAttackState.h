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
        //AnimStateMachine<Player>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value)
        {
            AnimStateMachine<Player>* machine = _owner->GetAnimStateMachine();
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
        /*else if constexpr (std::is_same<T, Monster>::value)
        {
            AnimStateMachine<Monster>* machine = _owner->GetAnimStateMachine();
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState((MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::JUMP:
                machine->ChangeAnimState((MonsterAnimState::JUMP));
                break;
            case MonsterAnimState::FALL:
                machine->ChangeAnimState((MonsterAnimState::FALL));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState((MonsterAnimState::DEATH));
                break;
            }
        }*/
    }

    virtual void Exit(T* _owner) override {}
};
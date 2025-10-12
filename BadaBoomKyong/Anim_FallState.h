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
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
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
            case PlayerAnimState::SPRINTING:
                machine->ChangeAnimState(int(PlayerAnimState::SPRINTING));
                break;
            case PlayerAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(int(PlayerAnimState::JUMP_ATTACK));
                break;
            case PlayerAnimState::DASH:
                machine->ChangeAnimState(int(PlayerAnimState::DASH));
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(int(PlayerAnimState::DEATH));
                break;
            case PlayerAnimState::LAND:
                machine->ChangeAnimState(int(PlayerAnimState::LAND));
                break;
            }           
        }        
        else if constexpr (std::is_same<T, Monster>::value)
        {            
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState(int(MonsterAnimState::IDLE));
                break;            
            case MonsterAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(int(MonsterAnimState::JUMP_ATTACK));
                break;
            case MonsterAnimState::DASH:
                machine->ChangeAnimState(int(MonsterAnimState::DASH));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(int(MonsterAnimState::DEATH));
                break;            
            }
        }
    }

    virtual void Exit(T* _owner) override 
    {        
    }
};
